#ifndef MGE_UTIL_LOG_H 
#define MGE_UTIL_LOG_H

#include <boost/noncopyable.hpp>
#include <ostream>
#include <string>
#include <set>
#include "OTeeStream.h"

namespace mge {

#undef ERROR // I think ENet does this on win32 for some reason, but its likely within the bowels of the windows headers it pulls in
	
	enum LogLevel {
		ERROR,
		WARNING,
		INFO,
		DEBUG,
		MAX_LOGLEVEL
	};

	const char *logLevelString(LogLevel level);
	LogLevel logLevelByName(const std::string &name);

	class Logger : public boost::noncopyable {
		public:
			Logger();

			void addStream(std::ostream &stream);
			void removeStream(std::ostream &stream);
			void setLogLevel(LogLevel maxlevel);

			std::ostream &log(const std::string &src, LogLevel level);

		private:
			typedef std::set<std::ostream *> StreamList;

			StreamList streams;
			OTeeStream<StreamList> logstream;

			LogLevel maxlevel;
	};
}

#endif
