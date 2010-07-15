#include "StandardFileStreamProducer.h"
#include "Exception.h"
#include <memory>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace mge;
using namespace std;

StandardFileStreamProducer::StandardFileStreamProducer() { }
StandardFileStreamProducer::~StandardFileStreamProducer() { }

istream *StandardFileStreamProducer::readFile(const string &str) { 
	auto_ptr<ifstream> stream(new ifstream(str.c_str(), ios_base::in | ios_base::binary));
	if (!stream->is_open())
		throw Exception(string("Failed to open ") + str + string(" for reading"));
	else
		return stream.release();
}

ostream *StandardFileStreamProducer::writeFile(const string &str) {
	auto_ptr<ofstream> stream(new ofstream(str.c_str(), ios_base::out | ios_base::binary));
	if (!stream->is_open())
		throw Exception(string("Failed to open ") + str + string(" for writing"));
	else
		return stream.release();
}

time_t StandardFileStreamProducer::getModTime(const string &filename) {
	struct stat data;
	if (stat(filename.c_str(), &data) != 0)
		return -1;
	return data.st_mtime;
}

StandardFileStreamProducer StandardFileStreamProducer::inst;
