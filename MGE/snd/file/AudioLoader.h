#ifndef MGE_SND_AUDIOLOADER_H
#define MGE_SND_AUDIOLOADER_H

#include <string>

namespace mge {
	class AudioFile;

	class AudioLoader {
		public:
			inline virtual ~AudioLoader() { }
			
			virtual AudioFile *openFile(const std::string &filename) = 0;
	};
}

#endif
