#include "WavLoader.h"
#include "WavFile.h"

using namespace mge;
using namespace std;

WavLoader::WavLoader(Logger &logger, FileStreamProducer &fsp) : logger(logger), fsp(fsp) { }
WavLoader::~WavLoader() { }

AudioFile *WavLoader::openFile(const std::string &filename) {
	if (filename.substr(filename.size() - 4, 4) == ".wav")
		return new WavFile(filename, logger, fsp);

	return NULL;
}
