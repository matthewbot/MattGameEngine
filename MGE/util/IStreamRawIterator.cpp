#include "IStreamRawIterator.h"
#include <cassert>

using namespace mge;
using namespace std;

IStreamRawIterator::IStreamRawIterator() : stream(NULL) { }
IStreamRawIterator::IStreamRawIterator(istream &stream) : stream(&stream) { ++*this; }

IStreamRawIterator &IStreamRawIterator::operator++() {
	assert(stream != NULL);
	
	if (stream->eof())
		stream = NULL;
	else
		val = stream->get();
		
	return *this;
}

IStreamRawIterator::value IStreamRawIterator::operator++(int) {
	int valcpy = val;
	++*this;
	return valcpy;
}

bool IStreamRawIterator::operator==(const IStreamRawIterator &other) {
	assert(other.stream == NULL);
	
	return stream == NULL;
}

int IStreamRawIterator::operator*() const {
	return val;
}	
