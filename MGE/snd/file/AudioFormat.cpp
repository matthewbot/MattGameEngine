#include "AudioFormat.h"
#include <MGE/util/Exception.h>
#include <sstream>
#include <ostream>
#include <AL/al.h>

using namespace mge;
using namespace std;

int AudioFormat::getALFormat() const {
	if (bits != 8 && bits != 16) {
		ostringstream buf;
		buf << "Invalid stream format with " << bits << " bits, only 8 and 16 bit audio is supported";
		throw Exception(buf.str());
	}

	if (channels > 2) {
		ostringstream buf;
		buf << "Invalid stream format with " << channels << " channels, only mono and stereo are supported";
		throw Exception(buf.str());
	}

	if (channels == 1) {
		if (bits == 8)
			return AL_FORMAT_MONO8;
		else
			return AL_FORMAT_MONO16;
	} else {
		if (bits == 8)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_STEREO16;
	}
}

ostream& mge::operator<<(ostream &out, const AudioFormat &format) {
	out << format.length << " bytes of ";

	if (format.channels == 1)
		out << "Mono ";
	else if (format.channels == 2)
		out << "Stereo ";
	else 
		out << format.channels << "-channel ";

	out << format.bits << "-bit ";
	out << format.freq/(float)1000.0 << " khz ";

	return out;
}
