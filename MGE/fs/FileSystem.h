#ifndef MGE_FS_FILESYSTEM_H
#define MGE_FS_FILESYSTEM_H

#include <MGE/kernel/KernelSystem.h>
#include <MGE/util/FileStreamProducer.h>
#include <istream>
#include <ostream>
#include <string>
#include <ctime>

namespace mge {
	class Logger;

	class FileSystem : public KernelSystem, public FileStreamProducer {
		public:
			FileSystem(const std::string &orgname, const std::string &appname, const char *argv0, Logger &logger);
			virtual ~FileSystem();
	
			std::string getBaseDir() const;

			void addLocation(const std::string &location);

			virtual std::istream *readFile(const std::string &name);
			virtual std::ostream *writeFile(const std::string &name);
			virtual std::time_t getModTime(const std::string &name);

			virtual const char *getName() const;
	};
}

#endif
