#ifndef MGE_SND_WAVSTREAM_H
#define MGE_SND_WAVSTREAM_H

#include <MGE/snd/file/AudioStream.h>
#include <istream>
#include <boost/scoped_ptr.hpp>

namespace mge {
	class WavStream : public AudioStream {
		friend class WavFile;

		public:
			virtual ~WavStream();

			virtual void load(char *buf, int length);
			virtual void rewind();
			virtual int available() const;

		private:
			WavStream(std::istream *stream, std::streamoff databegin, std::streamoff length); // for WavFile

		  boost::scoped_ptr<std::istream> stream;
			std::streamoff begin, length;
	};
}

#endif
