#include "MultiClip.h"
#include <MGE/snd/file/AudioFile.h>
#include <string>

using namespace mge;

using namespace std;

MultiClip::MultiClip(const string &name, SourceManager *sourceman, AudioFile *file, Logger &logger, int bufcount, size_t bufsize)
: BaseClip<MultiClipPlayback>(name, sourceman, logger),
	file(file), bufcount(bufcount), bufsize(bufsize) { }

MultiClip::~MultiClip() { }

ClipPlayback *MultiClip::makePlayback() {
	return new MultiClipPlayback(sourceman, this, logger);
}

