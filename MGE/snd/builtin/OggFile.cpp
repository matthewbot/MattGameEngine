#include "OggFile.h"
#include "OggStream.h"
#include "ovcallbacks.h"
#include <MGE/util/Exception.h>
#include <MGE/util/Logger.h>
#include <MGE/util/FileStreamProducer.h>
#include <vorbis/vorbisfile.h>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace mge;
using namespace std;

OggFile::OggFile(const string &file, Logger &logger, FileStreamProducer &fsp) : filename(file), logger(logger), fsp(fsp) {
	OggVorbis_File vf;

	istream *stream = fsp.readFile(file);
	int got;
	if ((got = ov_open_callbacks(stream, &vf, NULL, 0, istreamcallbacks)) != 0) {// will close/delete stream at ov_clear
		stringstream buf;
		buf << "Failed to open ogg file " << filename << " code " << got << endl;
		throw Exception(buf.str());
	}
	vorbis_info *info = ov_info(&vf, -1);

	fmt.channels = info->channels;
	fmt.freq = info->rate;
	fmt.length = (size_t)ov_pcm_total(&vf, -1);
	fmt.bits = 16;

	logger.log("audio", DEBUG) << "Determined format for OGG " << file << endl;
	logger.log("audio", DEBUG) << "  " << fmt << endl;

	ov_clear(&vf);
}

OggFile::~OggFile() { }

AudioStream *OggFile::makeStream() {
	return new OggStream(filename, fmt.bits/8 * fmt.channels, fsp);
}
