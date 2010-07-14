#ifndef MGE_SND_OGGFILE_H
#define MGE_SND_OGGFILE_H

#include <string>
#include <MGE/snd/file/AudioFile.h>

namespace mge {
	class Logger;
	class FileStreamProducer;
	class AudioStream;

	class OggFile : public AudioFile {
		friend class OggLoader;

		public:
			virtual ~OggFile();

			virtual AudioStream *makeStream();
		private:
			OggFile(const std::string &file, Logger &logger, FileStreamProducer &fsp);

			std::string filename;
			Logger &logger;
			FileStreamProducer &fsp;
	};
}

#endif
