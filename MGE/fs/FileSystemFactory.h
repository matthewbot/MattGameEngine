#ifndef MGE_FS_FILESYSTEMFACTORY_H
#define MGE_FS_FILESYSTEMFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>

namespace mge {
	class FileSystemFactory : public KernelSystemFactory {
		public:
			FileSystemFactory(const std::string &orgname, const std::string &appname, const char *argv0);
			virtual ~FileSystemFactory();
		
			virtual KernelSystem *makeKernelSystem(Logger &logger, const KernelSystemMap &map);
		
		private:
			std::string orgname, appname;
			const char *argv0;
	};
}

#endif
