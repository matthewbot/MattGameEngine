#include "MultiClipPlayback.h"
#include "MultiClip.h"
#include "bufutil.h"
#include <MGE/snd/file/AudioFile.h>
#include <MGE/snd/file/AudioStream.h>
#include <MGE/snd/system/SourceHandle.h>
#include <MGE/util/Logger.h>
#include <AL/al.h>
#include <memory>
#include <cmath>

using namespace mge;
using namespace std;

MultiClipPlayback::MultiClipPlayback(SourceManager *sourceman, MultiClip *clip, Logger &logger)
: BasePlayback<MultiClip>(sourceman, clip, logger),
  buf(new char [clip->bufsize]),
  stream(clip->file->makeStream())
{
	for (int i=0;i < clip->bufcount; i++)
		bufs_unqueued.push_back(getBufferID());
}

MultiClipPlayback::~MultiClipPlayback() {
	for (BufList::iterator i = bufs_unqueued.begin(); i != bufs_unqueued.end(); ++i) // delete all unqueued buffers
		freeBufferID(*i);

	for (BufSet::iterator i = bufs_queued.begin(); i != bufs_queued.end(); ++i)
		freeBufferID(*i);
}

void MultiClipPlayback::fillBufs() {
	ALint bufcount; 
	alGetSourcei(*source, AL_BUFFERS_PROCESSED, &bufcount); // get number of buffers we've used

	while (bufcount--) { // go through all of them
		ALuint buf;
		alSourceUnqueueBuffers(*source, 1, &buf); // get the buffer ID

		bufs_queued.erase(buf); // remove it from the queued set
		bufs_unqueued.push_back(buf); // and add it to the unqueued list
	}

	for (BufList::iterator bufptr = bufs_unqueued.begin(); bufptr != bufs_unqueued.end();) { // for every buffer in it
		if (fillBuf(*bufptr)) { // if we filled it
			alSourceQueueBuffers(*source, 1, &*bufptr); // queue it

			bufs_queued.insert(*bufptr); // add it to the queued set
			bufptr = bufs_unqueued.erase(bufptr); // and erase it from bufs_unqueued, advancing the iterator
		} else // couldn't fill it?
			break;  // don't bother with the rest, stream must be out
	}

	wantplay = !bufs_queued.empty(); // if there are no buffers queued, remove our want to play flag. This will change us from WAITING to STOPPED.
}

bool MultiClipPlayback::fillBuf(int bufid) {
	const AudioFormat &format = clip->file->getFormat(); // retrieve format

	if (stream->available() == 0) { // if theres no data from the stream
		if (getLoop()) // but we're supposed to loop
			stream->rewind(); // rewind the stream
		else // no looping
			return false; // we're done, don't read anymore
	}

	size_t amt = min(clip->bufsize, stream->available()); // get the amount to read
	stream->load(buf.get(), amt); // load it from the stream

	alBufferData(bufid, format.getALFormat(), buf.get(), amt, format.freq); // shove it in the buffer
	return true;
}

void MultiClipPlayback::start() {
	State state = getState();

	if (state != PAUSED) {
		alSourcei(*source, AL_BUFFER, 0); // unqueues all buffers
		alSourcei(*source, AL_LOOPING, 0); // remove loop attribute

		bufs_unqueued.insert(bufs_unqueued.end(), bufs_queued.begin(), bufs_queued.end()); // add all queued buffers to the unqueued set
		bufs_queued.clear(); // clear the queued set

		stream->rewind(); // rewind the stream

		fillBufs(); // and filler up
	}
}

void MultiClipPlayback::update() {
	State state = getState();

	if (state == STOPPED || state == PAUSED)
		return;

	fillBufs();

	if (state != PLAYING && wantplay) { // if we still want to be played but weren't
		logger.log("audio", WARNING) << "MultiClip " << clip->getName() << " went dry" << endl;
		alSourcePlay(*source);
	}
}

void MultiClipPlayback::setLoop(bool loop) {
	ClipPlayback::setLoop(loop);
}

