#ifndef MGE_UTIL_OTEESTREAM_H
#define MGE_UTIL_OTEESTREAM_H

#include <ostream>

namespace mge {
	template <typename Cont> class OTeeStream : public std::ostream {
	public:
		OTeeStream(Cont &cont) : std::ios(&tbuf), std::ostream(&tbuf), tbuf(cont) { }
			
	private:
		struct TeeBuf : std::streambuf {
			Cont &streams;
		
			TeeBuf(Cont &cont) : streams(cont) { }

			inline virtual int overflow(int c) {
				for (typename Cont::iterator i = streams.begin(); i != streams.end(); ++i) {
					(*i)->put(c);
				}

				return 1;
			}
		};

		TeeBuf tbuf;
	};
}

#endif
