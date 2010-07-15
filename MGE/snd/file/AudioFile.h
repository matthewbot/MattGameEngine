#ifndef MGE_SND_AUDIOFILE_H
#define MGE_SND_AUDIOFILE_H

#include "AudioFormat.h"

namespace mge {
	class AudioStream;

	class AudioFile {
		public:
			inline virtual ~AudioFile() { }

			virtual AudioStream *makeStream() = 0;
			inline const AudioFormat &getFormat() { return fmt; }

		protected:
			AudioFormat fmt;
	};
}

#endif
