#ifndef MGE_SND_WAVFILE_H
#define MGE_SND_WAVFILE_H

#include <MGE/snd/file/AudioFile.h>
#include <string>

namespace mge {
	class Logger;
	class FileStreamProducer;

	class WavFile : public AudioFile {
		friend class WavLoader;

		public:
			virtual ~WavFile();
			virtual AudioStream *makeStream();

		private:
			WavFile(const std::string &filename, Logger &logger, FileStreamProducer &fsp); // for WavLoader

			const std::string filename;
			FileStreamProducer &fsp;
	};
}

#endif
