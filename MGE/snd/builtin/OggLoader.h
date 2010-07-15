#ifndef MGE_SND_OGGLOADER_H
#define MGE_SND_OGGLOADER_H

#include <string>
#include <MGE/snd/file/AudioLoader.h>

namespace mge {
	class Logger;
	class FileStreamProducer;

	class OggLoader : public AudioLoader {
		public:
			OggLoader(Logger &logger, FileStreamProducer &fsp);
			virtual ~OggLoader();

			virtual AudioFile *openFile(const std::string &file);
		private:
			Logger &logger;
			FileStreamProducer &fsp;
	};
}

#endif
