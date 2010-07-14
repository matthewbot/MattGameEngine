#include "FileSystem.h"
#include <MGE/fs/impl/fsimpl.h>
#include <MGE/util/Exception.h>
#include <physfs.h>

using namespace mge;
using namespace std;

FileSystem::FileSystem(const std::string &orgname, const std::string &appname, const char *argv0, Logger &logger) {
	if (!PHYSFS_init(argv0))
		throw Exception("Failed to init PhysFS");
		
	if (!PHYSFS_setSaneConfig(orgname.c_str(), appname.c_str(), "dat", false, true))
		throw Exception("Failed to configure PhysFS");
}

FileSystem::~FileSystem() {
	if (!PHYSFS_deinit())
		throw Exception("Failed to deinit PhysFS");
}

string FileSystem::getBaseDir() const {
	return string(PHYSFS_getBaseDir());
}

void FileSystem::addLocation(const string &location) {
	if (!PHYSFS_addToSearchPath(location.c_str(), true))
		throw Exception(string("Failed to add ") + location + string(" to search path"));
}

istream *FileSystem::readFile(const string &name) {
	PHYSFS_File *file;

	if ((file = PHYSFS_openRead(name.c_str())) == NULL)
		throw Exception(string("Failed to open ") + name + string(" for reading"));

	return new PhysFSIStream(file, 4096);
}

ostream *FileSystem::writeFile(const string &name) {
	PHYSFS_File *file;

	if ((file = PHYSFS_openWrite(name.c_str())) == NULL)
		throw Exception(string("Failed to open ") + name + string(" for writing"));

	return new PhysFSOStream(file, 4096);
}

time_t FileSystem::getModTime(const string &name) {
	return (time_t)PHYSFS_getLastModTime(name.c_str());
}

const char *FileSystem::getName() const {
	return "FileSystem";
}
