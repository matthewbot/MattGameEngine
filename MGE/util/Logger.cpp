#include "Logger.h"
#include "Exception.h"
#include "algorithm.h"
#include "ONullStream.h"
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace mge;
using namespace std;

Logger::Logger() : streams(), logstream(streams) {
	maxlevel = INFO;
}

void Logger::addStream(std::ostream &stream) {
	streams.insert(&stream);
}

void Logger::removeStream(std::ostream &stream) {
	streams.erase(&stream);
}

void Logger::setLogLevel(LogLevel maxlevel) {
	this->maxlevel = maxlevel;
}

ostream &Logger::log(const string &src, LogLevel level) {
	if (level > maxlevel)
		return ONullStream::inst;

	time_t rawtime;
	time(&rawtime);

	char timebuf[15];
	strftime(timebuf, sizeof(timebuf), "<%H:%M:%S>", localtime(&rawtime));

	stringstream msgbuf;
	msgbuf << timebuf << " [" << src << " " << logLevelString(level) << "]";
	msgbuf << string(max<int>(25 - msgbuf.str().length(), 0), ' '); // add spaces to line up text nicely
	
	logstream << msgbuf.str();
	return logstream;
}


static const char *logstr[] = {
	"error",
	"warning",
	"info",
	"debug",
};

const char *mge::logLevelString(LogLevel level) {
	return logstr[level];
}

LogLevel mge::logLevelByName(const string &str) {
	string lstr(str_tolower(str));

	if (lstr == "error")
		return ERROR;
	else if (lstr == "warning")
		return WARNING;
	else if (lstr == "info")
		return INFO;
	else if (lstr == "debug")
		return DEBUG;
	else
		throw Exception(string("Bad LogLevel ") + str);
}
