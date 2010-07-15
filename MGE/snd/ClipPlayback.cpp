#include "ClipPlayback.h"
#include <MGE/snd/system/SourceManager.h>
#include <MGE/snd/system/SourceHandle.h>
#include <MGE/util/Exception.h>
#include <AL/al.h>
#include <sstream>

using namespace std;
using namespace mge;


ClipPlayback::ClipPlayback(SourceManager *sourceman) 
: wantplay(false),
  sourceman(sourceman), 
	xpos(0), ypos(0),
	mindist(0), maxdist(1000),
	pitch(1), gain(1),
	relative(false),
	priority(0),
	loop(false) { }

ClipPlayback::~ClipPlayback() {
	if (source)
		alSourceStop(*source); // TODO refactor stuff like this into a SourceHandle
}

void ClipPlayback::getSource() {
	if (source) // if we've already got a source
		return; // we're done
	
	source = sourceman->getSource(priority); // ask the audiosystem for one
	if (!source) // if they couldn't give us one
		return; // we're done

	alSource3f(*source, AL_POSITION, xpos, ypos, 0); // we got a new source, set it up according to our properties
	alSourcei(*source, AL_SOURCE_RELATIVE, relative);
	alSource3f(*source, AL_DIRECTION, 0, 0, 0);
	alSourcef(*source, AL_PITCH, pitch);
	alSourcef(*source, AL_GAIN, gain);
	alSourcef(*source, AL_REFERENCE_DISTANCE, mindist);
	alSourcef(*source, AL_MAX_DISTANCE, maxdist);
}

void ClipPlayback::play() {
	wantplay = true;
	getSource();
	if (source) {
		start();
		alSourcePlay(*source);
	}
}

void ClipPlayback::pause() {
	wantplay = false;
	if (source)
		alSourcePause(*source);
}

void ClipPlayback::stop() {
	wantplay = false;
	if (source)
		alSourceStop(*source);
}

ClipPlayback::State ClipPlayback::getState() const {
	if (!source)
		return wantplay ? WAITING : STOPPED;

	ALint state;
	alGetSourcei(*source, AL_SOURCE_STATE, &state);
	switch (state) {
		case AL_PLAYING:
			return PLAYING;

		case AL_STOPPED:
		case AL_INITIAL:
			return wantplay ? WAITING : STOPPED;

		case PAUSED:
			return PAUSED;

		default:
			{
				ostringstream outbuf;
				outbuf << "Unknown OpenAL source state " << state;
				throw Exception(outbuf.str());
			}
			break;
	}
}

void ClipPlayback::setPos(float x, float y) {
	xpos = x; ypos = y;

	if (source)
		alSource3f(*source, AL_POSITION, xpos, ypos, 0);
}

void ClipPlayback::setGain(float g) {
	gain = g;

	if (source)
		alSourcef(*source, AL_GAIN, gain);
}

void ClipPlayback::setRelative(bool rel) {
	relative = rel;

	if (source)
		alSourcef(*source, AL_SOURCE_RELATIVE, relative);
}

void ClipPlayback::setDist(float min, float max) {
	mindist = min; maxdist = max;

	if (source) {
		alSourcef(*source, AL_REFERENCE_DISTANCE, mindist);
		alSourcef(*source, AL_MAX_DISTANCE, maxdist);
	}
}

void ClipPlayback::setPitch(float pitch) {
	this->pitch = pitch;

	if (source)
		alSourcef(*source, AL_PITCH, pitch);
}

void ClipPlayback::setLoop(bool loop) {
	this->loop = loop;
}
