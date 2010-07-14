#ifndef MGE_SND_AUDIOSTREAM_H
#define MGE_SND_AUDIOSTREAM_H

namespace mge {
	class AudioStream {
		public:
			inline virtual ~AudioStream() { }

			virtual void load(char *buf, int length) = 0;
			virtual void rewind() = 0;
			virtual int available() const = 0;
	};
}

#endif
