#include "fsimpl.h"

using namespace mge;
using namespace std;

PhysFSOStream::PhysFSOStream(PHYSFS_File *file, size_t bufsize) : ostream(&buf),  buf(file, bufsize) { }
PhysFSOStream::~PhysFSOStream() { }
