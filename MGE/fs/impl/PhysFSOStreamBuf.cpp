#include "fsimpl.h"
#include <MGE/util/Exception.h>
#include <physfs.h>

using namespace std;
using namespace mge;

PhysFSOStreamBuf::PhysFSOStreamBuf(PHYSFS_File *file, size_t bufsize) : PhysFSStreamBufBase(file, bufsize) {
	setp(&bufdata[0], &bufdata[bufdata.size()]);
}

int PhysFSOStreamBuf::sync() {
  char *begin = pbase();
	char *end = pptr();

	if (PHYSFS_write(file, begin, 1, end-begin) != (end - begin))
		throw Exception("Failed to flush buffer");

	setp(begin, epptr());

	return 0;
}

int PhysFSOStreamBuf::overflow(int c) {
	sync();

	*pptr() = c;
	pbump(1);

	return 0;
}

void PhysFSOStreamBuf::clearBuf() {
	sync();
}
