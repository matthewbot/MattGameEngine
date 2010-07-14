#include "SourceManager.h"
#include <MGE/snd/ClipPlayback.h>
#include "SourceHandle.h"
#include <MGE/util/Logger.h>
#include <AL/al.h>

using namespace mge;
using namespace std;
using namespace boost;

SourceManager::SourceManager(Logger &logger) : logger(logger) {
	int sourcecount = 0;
	while (sourcecount < 16) {
		ALuint id;

		alGenSources(1, &id);
		if (alGetError() != AL_NO_ERROR)
			break;

		sources.push_back(make_pair(id, weak_ptr<SourceHandle>()));
		sourcecount++;
	}

	logger.log("audio", DEBUG) << "Created " << sourcecount << " sources" << endl;
}

SourceManager::~SourceManager() {
	for (SourceList::iterator i = sources.begin(); i != sources.end(); ++i) {
		ALuint id = i->first;
		alDeleteSources(1, &id);
	}
}


shared_ptr<SourceHandle> SourceManager::getSource(int priority) {
	SourceList::iterator cursource = sources.end();

	// step 1, look for a source that doesn't have a player, or one that isn't currently playing
	for (SourceList::iterator i = sources.begin(); i != sources.end(); ++i) {
		bool avail = false;
		int &id = i->first;
	  weak_ptr<SourceHandle> &handle = i->second;

		if (handle.expired()) {
			avail = true;
		} else {
			ALint status; 
			alGetSourcei(id, AL_SOURCE_STATE, &status);

			if (status == AL_STOPPED || status == AL_INITIAL)
				avail = true;
		}

		if (avail) {
			cursource = i; 
			break;
		}
	}

	// step 2, look for a source that is playing but with a player with a lower priority
	if (cursource == sources.end()) {
		int minpri = priority;

		for (SourceList::iterator i = sources.begin(); i != sources.end(); ++i) {
	  	shared_ptr<SourceHandle> handle(i->second); // this is safe (weak -> shared), because if we get here we know every source already has a player

			int pri = handle->getPriority(); 
			if (pri < minpri) {
				minpri = pri;
				cursource = i;
			}
		}
	}

	// if we still got nothing
	if (cursource == sources.end())
		return shared_ptr<SourceHandle>(); // we're done

	
	shared_ptr<SourceHandle> prevhandle(cursource->second.lock());
	if (prevhandle) { // if our source has a player currently
		logger.log("audio", DEBUG) << "Stole source from player pri " << prevhandle->getPriority() << " for one pri " << priority << endl;
		prevhandle->clearSource(); // inform them that they lost it
	}
	
	int id = cursource->first; 
	shared_ptr<SourceHandle> newhandle(new SourceHandle(id, priority)); // construct new handle
	cursource->second = newhandle; // set it to the sources list

	alSourceStop(id); // stop the source, in case its still playing
	alSourcei(id, AL_BUFFER, AL_NONE); // then remove any buffer it might've had
	return newhandle;
}
