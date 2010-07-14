#include "ONullStream.h"

using namespace mge;

ONullStream::ONullStream() : std::ostream(&sbuf) { }
int ONullStream::NullBuf::overflow(int c) { return 0; }

ONullStream ONullStream::inst;
