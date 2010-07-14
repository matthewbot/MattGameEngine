#include "WavFile.h"
#include "WavStream.h"
#include <MGE/util/Exception.h>
#include <MGE/util/Logger.h>
#include <MGE/util/FileStreamProducer.h>
#include <fstream>
#include <cstring>
#include <boost/cstdint.hpp>
#include <boost/scoped_ptr.hpp>

using namespace mge;
using namespace std;
using namespace boost;

struct wavheader {
	struct {
		char riff[4];
		uint32_t file_length;
		char wave[4];
	} riff_header;
	struct {
		char fmt[4];
		uint32_t length;
		uint16_t format;
		uint16_t channels;
		uint32_t samplerate;
		uint32_t bytespersecond;
		uint16_t blockalign;
		uint16_t samplebits;
	} fmt_header;
	struct {
		char data[4];
		uint32_t length;
	} data_header;
};

static const char riff_val[4] = {'R', 'I', 'F', 'F'};
static const char wave_val[4] = {'W', 'A', 'V', 'E'};
static const char fmt_val[4] = {'f', 'm', 't', ' '};
static const char data_val[4] = {'d', 'a', 't', 'a'};

WavFile::WavFile(const string &fname, Logger &logger, FileStreamProducer &fsp) : filename(fname), fsp(fsp) {
	struct wavheader header;
	{
		boost::scoped_ptr<istream> file(fsp.readFile(filename.c_str())); // open the file

		file->read((char *)&header, sizeof(header)); // read the header
	}

	if (memcmp(&header.riff_header.riff, riff_val, sizeof(riff_val)) != 0)
		throw Exception(string("Bad RIFF header in wav file ") + filename);

	if (memcmp(&header.riff_header.wave, wave_val, sizeof(wave_val)) != 0)
		throw Exception(string("Bad WAVE header in wav file ") + filename);

	if (memcmp(&header.fmt_header.fmt, fmt_val, sizeof(fmt_val)) != 0)
		throw Exception(string("Bad fmt header in wav file ") + filename);

	if (memcmp(&header.data_header.data, data_val, sizeof(data_val)) != 0)
		throw Exception(string("Bad data header in wav file ") + filename);

	fmt.channels = header.fmt_header.channels;
	fmt.bits = header.fmt_header.samplebits;
	fmt.freq = header.fmt_header.samplerate;
	fmt.length = header.data_header.length;

	logger.log("audio", DEBUG) << "Loaded WAV " << filename << endl;
	logger.log("audio", DEBUG) << "  " << fmt << endl;
}

WavFile::~WavFile() { 

}

AudioStream *WavFile::makeStream() {
	istream *stream = fsp.readFile(filename);
	return new WavStream(stream, sizeof(wavheader), fmt.length);
}
