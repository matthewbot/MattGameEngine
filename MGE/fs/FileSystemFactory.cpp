#include "FileSystemFactory.h"
#include "FileSystem.h"

using namespace mge;
using namespace std;

FileSystemFactory::FileSystemFactory(const string &orgname, const string &appname, const char *argv0)
 : orgname(orgname), appname(appname), argv0(argv0) { }
FileSystemFactory::~FileSystemFactory() { }

KernelSystem *FileSystemFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	return new FileSystem(orgname, appname, argv0, logger);
}
