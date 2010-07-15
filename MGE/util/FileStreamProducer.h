#ifndef MGE_UTIL_FSP_H
#define MGE_UTIL_FSP_H

#include <istream>
#include <ostream>
#include <string>
#include <ctime>

namespace mge {
	class FileStreamProducer {
		public:
			inline virtual ~FileStreamProducer() { }

			virtual std::istream *readFile(const std::string &str) = 0; // throw Exception on fail
			virtual std::ostream *writeFile(const std::string &str) = 0;
			virtual std::time_t getModTime(const std::string &str) = 0;
	};
}

#endif
