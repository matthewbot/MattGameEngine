#include "ovcallbacks.h"
#include <istream>

using namespace mge;
using namespace std;

static size_t readfunc(void *ptr, size_t size, size_t num, void *datasource);
static int seekfunc(void *datasource, ogg_int64_t offset, int whence);
static int closefunc(void *datasource);
static long tellfunc(void *datasource);

const ov_callbacks mge::istreamcallbacks = { &readfunc, &seekfunc, &closefunc, &tellfunc }; // no seeking currently

static size_t readfunc(void *ptr, size_t size, size_t num, void *datasource) {
	istream *stream = (istream *)datasource;
	if (stream->eof())
		return 0;
	
  stream->read((char *)ptr, size*num);
  int got = stream->gcount();
	return got;
}

static int seekfunc(void *datasource, ogg_int64_t offset, int whence) {
	istream *stream = (istream *)datasource;
	ios_base::seekdir dir;
	
	switch (whence) {
		case SEEK_SET:
			dir = ios_base::beg;
			stream->clear();
			break;
			
		case SEEK_CUR:
			dir = ios_base::cur;
			stream->clear();
			break;
			
		case SEEK_END:
			dir = ios_base::end;
			if (offset < 0)
				stream->clear();
			break;
	}
	
	stream->seekg((streamoff)offset, dir);
	if (stream->fail())
		return -1;
	else
		return 0;
}

static int closefunc(void *datasource) {
	istream *stream = (istream *)datasource;
	
	delete stream;
	return true;
}

static long tellfunc(void *datasource) {
	istream *stream = (istream *)datasource;
	
	return (long)stream->tellg();
}
