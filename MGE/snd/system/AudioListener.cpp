#include "AudioListener.h"
#include <AL/al.h>
#include <cmath>

using namespace mge;
using namespace std;

AudioListener::AudioListener() {
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
	alListener3f(AL_VELOCITY, 0, 0, 0);

	// use our own setters to initialize both our members and OpenAL state
	setPos(0, 0);
	setRotation(90);
	setGain(1);
}

void AudioListener::setPos(float x, float y) {
	xpos = x; ypos = y;

	alListener3f(AL_POSITION, x, y, 0);
}

static const float degtorad = (float)(3.1415926535897932384626433832795 / 180);

void AudioListener::setRotation(float rotation) {
	rotation *= degtorad; // convert to degrees
	this->rot = rotation;

	float orientation[6] = { cos(rotation), sin(rotation), 0, 0, 0, -1 }; // compute the at and up vectors 
	alListenerfv(AL_ORIENTATION, orientation); // pass to OpenAL
}

void AudioListener::setGain(float gain) {
	this->gain = gain;

	alListenerf(AL_GAIN, gain);
}

