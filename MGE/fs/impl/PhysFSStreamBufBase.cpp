#include "fsimpl.h"
#include <MGE/util/Exception.h>

using namespace std;
using namespace mge;

PhysFSStreamBufBase::PhysFSStreamBufBase(PHYSFS_File *file, size_t bufsize) : bufdata(bufsize) {
	this->file = file;
}

PhysFSStreamBufBase::~PhysFSStreamBufBase() {
	if (!PHYSFS_close(file))
		throw Exception("Failed to close file");
}

streampos PhysFSStreamBufBase::seekoff(streamoff off, ios_base::seekdir way, ios_base::openmode which) {
	if (!(which | ios_base::in))
		return 0;

	PHYSFS_sint64 base;

	switch (way) {
		case ios_base::beg:
			base = 0;
			break;

		case ios_base::cur:
			base = PHYSFS_tell(file);
			if (base == -1)
				throw Exception("Failed to tell on file");
			break;

		case ios_base::end:
			base = PHYSFS_fileLength(file);
			if (base == -1)
				throw Exception("Failed to determine length of file");
			break;
	}

	return seekpos((streamoff)(base + off), ios_base::in);
}

streampos PhysFSStreamBufBase::seekpos(streampos pos, ios_base::openmode which) {
	if (!(which | ios_base::in))
		return 0;

	if (!PHYSFS_seek(file, pos))
		throw Exception("Failed to seek on file");

	clearBuf();

	return pos;
}
