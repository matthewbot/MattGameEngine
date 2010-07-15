#include "SingleClipPlayback.h"
#include "SingleClip.h"
#include <MGE/snd/system/SourceHandle.h>
#include <MGE/util/Logger.h>
#include <AL/al.h>

using namespace mge;
using namespace std;

SingleClipPlayback::SingleClipPlayback(SourceManager *sourceman, SingleClip *clip, Logger &logger) 
: BasePlayback<SingleClip>(sourceman, clip, logger) { }

SingleClipPlayback::~SingleClipPlayback() { }

void SingleClipPlayback::start() {
	State state = getState();

	if (state == PLAYING)
		alSourceRewind(*source);
	else if (state == WAITING) {
		alSourcei(*source, AL_BUFFER, clip->getBufID());
		alSourcei(*source, AL_LOOPING, (wantplay = getLoop()) ? AL_TRUE : AL_FALSE);
	} // if paused, we're already ready to go, just push play
}

void SingleClipPlayback::setLoop(bool loop) {
	ClipPlayback::setLoop(loop);
	if (source) {
		alSourcei(*source, AL_LOOPING, loop);

		if (getState() == PLAYING)
			wantplay = loop;
	}
}

void SingleClipPlayback::update() {
	if (getState() == WAITING) // if we're still attempting to start
		play(); // attempt again
}
