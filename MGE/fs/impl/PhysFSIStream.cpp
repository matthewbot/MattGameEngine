#include "fsimpl.h"

using namespace mge;
using namespace std;

PhysFSIStream::PhysFSIStream(PHYSFS_File *file, size_t bufsize) : istream(&buf), buf(file, bufsize, 8) { }
PhysFSIStream::~PhysFSIStream() { }
