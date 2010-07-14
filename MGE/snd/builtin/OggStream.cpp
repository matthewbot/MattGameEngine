#include "OggStream.h"
#include "ovcallbacks.h"
#include <MGE/util/Exception.h>
#include <MGE/util/FileStreamProducer.h>
#include <vorbis/vorbisfile.h>
#include <iostream>

using namespace mge;
using namespace std;

struct OggStream::VBdata {
	OggVorbis_File vf;
};

OggStream::OggStream(const string &filename, int bytespersample, FileStreamProducer &fsp)
: filename(filename), bytespersample(bytespersample), data(new VBdata()), fsp(fsp) {
	istream *stream = fsp.readFile(filename);
	if (ov_open_callbacks(stream, &data->vf, NULL, 0, istreamcallbacks) != 0)
		throw Exception(string("Failed to open OggStream for ") + filename);
}

OggStream::~OggStream() {
	ov_clear(&data->vf);
}

void OggStream::load(char *buf, int length) {
	if (length > available())
		throw Exception("Attempting to read more from OggStream than is available");

	atbeginning = false;

	int unused;
	int tries=0;
	while (length > 0) {
		tries++;
		long got = ov_read(&data->vf, buf, length, 0, 2, 1, &unused); // read as much as we can
		
		if (got > 0) { // if we managed to read some
			buf += got; // advance the buffer pointer
			length -= got; // decrease the length by the amount we got
		} else if (got == 0) // got nothing, its an EOF
			break; // so end the loop
	}
}

int OggStream::available() const {
	return (ov_pcm_total(&data->vf, -1) - ov_pcm_tell(&data->vf))*bytespersample;
}

void OggStream::rewind() {
	if (atbeginning)
		return;

	ov_clear(&data->vf);
	istream *stream = fsp.readFile(filename);
	if (ov_open_callbacks(stream, &data->vf, NULL, 0, istreamcallbacks) != 0)
		throw Exception(string("Failed to rewind OggStream for ") + filename);
	atbeginning = true;
}
