#ifndef MGE_SND_AUDIOFORMAT_H
#define MGE_SND_AUDIOFORMAT_H

#include <ostream>

namespace mge {
	struct AudioFormat {
		int channels;
		int bits;
		int freq;
		size_t length; // in bytes

		int getALFormat() const;
	};
	
	std::ostream& operator<<(std::ostream &out, const AudioFormat &format);
}

#endif
