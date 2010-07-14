#ifndef MGE_UTIL_ISTREAMRAWITERATOR_H
#define MGE_UTIL_ISTREAMRAWITERATOR_H

#include <istream>

namespace mge {
	class IStreamRawIterator {
	public:
		struct value {
			int val;
			inline value(int i) { val = i; }
			inline int operator*() { return val; }
		};

		IStreamRawIterator();
		IStreamRawIterator(std::istream &stream);

		IStreamRawIterator &operator++();
		value operator++(int);
		bool operator==(const IStreamRawIterator &i);
		int operator*() const;
	
	private:
		std::istream *stream;
		int val;
	};
}

#endif
