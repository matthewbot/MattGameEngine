#include "fsimpl.h"
#include <physfs.h>

using namespace std;
using namespace mge;

PhysFSIStreamBuf::PhysFSIStreamBuf(PHYSFS_File *file, size_t bufsize, size_t putsize) : PhysFSStreamBufBase(file, bufsize) {
	this->putsize = putsize;
	clearBuf();
}

int PhysFSIStreamBuf::underflow() {
    if (gptr() < egptr()) // buffer not exhausted
        return *gptr(); // return character

	if (PHYSFS_eof(file))
		return -1;

	char *back = eback();

	char *begin = back + putsize;
	char *end = egptr();
	int got = (int)PHYSFS_read(file, begin, 1, end-begin);

	setg(back, begin, begin+got);
	return *reinterpret_cast<unsigned char *>(begin);
}

void PhysFSIStreamBuf::clearBuf() {
	setg(&bufdata[0], &bufdata[bufdata.size()-1]+1, &bufdata[bufdata.size()-1]+1);
}

