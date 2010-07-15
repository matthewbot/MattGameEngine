#include "WavStream.h"
#include <MGE/util/Exception.h>
#include <istream>
#include <cstring>
#include <cassert>

using namespace mge;
using namespace std;

WavStream::WavStream(istream *stream, streamoff begin, streamoff length)
 : stream(stream), begin(begin), length(length) {
	stream->seekg(begin);
}

WavStream::~WavStream() { }

void WavStream::rewind() {
	stream->clear();
	stream->seekg(begin);
}

void WavStream::load(char *buf, int length) {
	if (length > available())
		throw Exception("Attempt to load more bytes from wav than are currently available");

	stream->read(buf, length);
}

int WavStream::available() const {
	return length - (stream->tellg() - begin);
}
