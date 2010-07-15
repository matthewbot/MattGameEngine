#ifndef MGE_SND_WAVLOADER_H
#define MGE_SND_WAVLOADER_H

#include <string>
#include <MGE/snd/file/AudioLoader.h>

namespace mge {
	class Logger;
	class AudioFile;
	class FileStreamProducer;

	class WavLoader : public AudioLoader {
		public:
			WavLoader(Logger &logger, FileStreamProducer &fsp);
			virtual ~WavLoader();

			virtual AudioFile *openFile(const std::string &filename);
		private:
			Logger &logger;
			FileStreamProducer &fsp;
	};
}

#endif
