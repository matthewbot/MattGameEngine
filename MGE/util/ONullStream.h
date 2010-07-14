#ifndef MGE_UTIL_ONULLSTREAM_H
#define MGE_UTIL_ONULLSTREAM_H

#include <ostream>

namespace mge {
	class ONullStream : public std::ostream {
	public:
		ONullStream();

		static ONullStream inst;
	private:
		struct NullBuf : std::streambuf {
			virtual int overflow(int c);
		};

		NullBuf sbuf;
	};
}

#endif
