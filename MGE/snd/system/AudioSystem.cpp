#include "AudioSystem.h"
#include <MGE/snd/file/AudioFile.h>
#include <MGE/snd/file/AudioLoader.h>
#include <MGE/snd/impl/MultiClip.h>
#include <MGE/snd/impl/SingleClip.h>
#include <MGE/util/Exception.h>
#include <MGE/util/Logger.h>

#include <AL/al.h>
#include <AL/alc.h>

using namespace std;
using namespace mge;
using namespace boost;

AudioSystem::AudioSystem(Logger &logger) 
: logger(logger),
	subsystem(logger),
  sources(logger) { }

AudioSystem::~AudioSystem() { }


void AudioSystem::addLoader(AudioLoader *loader) {
	loaders.push_back(loader);
}

shared_ptr<Clip> AudioSystem::loadClip(const string &filename, bool stream) {
	AudioFile *file = NULL;

	for (LoaderList::iterator i = loaders.begin(); i != loaders.end(); ++i) {
		file = (*i)->openFile(filename);
		if (file)
			break;
	}
	
	if (!file)
		throw Exception(string("No AudioFileLoader could load ") + filename);

	shared_ptr<Clip> clip;
	if (stream)
		clip = shared_ptr<Clip>(new MultiClip(filename, &sources, file, logger, 3, 8*1024));
	else
		clip = shared_ptr<Clip>(new SingleClip(filename, &sources, file, logger));

	clips.push_back(clip);
	return clip;
}


SystemUpdateValue AudioSystem::update() {
	for (ClipList::iterator i = clips.begin(); i != clips.end();) {
		shared_ptr<Clip> clipptr = i->lock();
		if (clipptr) {
			clipptr->updatePlayback();
			++i;
		} else
			i = clips.erase(i);
	}

	return NONE;
}

const char *AudioSystem::getName() const { return "AudioSystem"; }



struct AudioSystem::SubSystemHandler::ALdata {
	ALdata() : device(NULL), context(NULL) { }

	ALCdevice *device;
	ALCcontext *context;
};

AudioSystem::SubSystemHandler::SubSystemHandler(Logger &logger) : aldata(new ALdata()) {
	aldata->device = alcOpenDevice(NULL); // open whatever device we can get
	if (!aldata->device) 
		throw Exception("Failed to open default audio device");

	logger.log("audio", INFO) << "Opened default audio device, got " << alcGetString(aldata->device, ALC_DEVICE_SPECIFIER) << endl;

	aldata->context = alcCreateContext(aldata->device, NULL); // create a context with any settings
	if (!aldata->context) 
		throw Exception("Failed to create default context");

	alcMakeContextCurrent(aldata->context); // and start using it

	logger.log("audio", INFO) << "Created default context" << endl;
	logger.log("audio", INFO) << "  AL_VERSION: " << alGetString(AL_VERSION) << endl;
	logger.log("audio", INFO) << "  AL_RENDERER: " << alGetString(AL_RENDERER) << endl;
}

AudioSystem::SubSystemHandler::~SubSystemHandler() {
	if (aldata->context) {
		alcMakeContextCurrent(NULL);
		alcDestroyContext(aldata->context);
	}
		
	if (aldata->device)
		alcCloseDevice(aldata->device);
}
