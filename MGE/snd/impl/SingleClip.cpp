#include "SingleClip.h"
#include <MGE/snd/file/AudioFormat.h>
#include <MGE/snd/file/AudioFile.h>
#include <MGE/snd/file/AudioStream.h>
#include "bufutil.h"
#include "SingleClipPlayback.h"
#include <MGE/util/Exception.h>
#include <AL/al.h>
#include <sstream>
#include <memory>

using namespace std;
using namespace mge;


SingleClip::SingleClip(const string &name, SourceManager *sourceman, AudioFile *fileptr, Logger &logger)
: BaseClip<SingleClipPlayback>(name, sourceman, logger) {

	auto_ptr<AudioFile> file(fileptr); // clean up the audio file when we're done
	AudioFormat format = file->getFormat();
	ALenum alformat = format.getALFormat();

	auto_ptr<AudioStream> stream(file->makeStream()); // will delete the stream for us on exit
	int length = stream->available(); // determine how much is in the stream

	auto_ptr<char> buf(new char [length]); // allocate enough memory
	stream->load(buf.get(), length); // read it all in

	bufid = getBufferID(); // allocate the single buffer
	alBufferData(bufid, alformat, buf.get(), length, format.freq); // fill it with data
	if (alGetError() != AL_NO_ERROR)
		throw Exception("Error while building audio buffer");
}

SingleClip::~SingleClip() {
	freeBufferID(bufid); // free the single buffer
}

ClipPlayback *SingleClip::makePlayback() {
	return new SingleClipPlayback(sourceman, this, logger);
}
