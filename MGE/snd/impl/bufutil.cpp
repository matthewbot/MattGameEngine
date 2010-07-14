#include "bufutil.h"
#include <AL/al.h>

using namespace mge;

int mge::getBufferID() {
	ALuint buf;
	alGenBuffers(1, &buf);
	return buf;
}

void mge::freeBufferID(int bufid) {
	ALuint buf = bufid;
	alDeleteBuffers(1, &buf);
}

