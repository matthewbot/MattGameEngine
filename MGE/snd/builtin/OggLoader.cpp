#include "OggLoader.h"
#include "OggFile.h"

using namespace mge;

using namespace std;

OggLoader::OggLoader(Logger &logger, FileStreamProducer &fsp) : logger(logger), fsp(fsp) { }
OggLoader::~OggLoader() { }

AudioFile *OggLoader::openFile(const std::string &filename) {
	if (filename.substr(filename.size() - 4, 4) == ".ogg")
		return new OggFile(filename, logger, fsp);

	return NULL;
}
