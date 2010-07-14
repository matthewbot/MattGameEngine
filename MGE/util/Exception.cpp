#include "Exception.h"
#include <string>

using namespace mge;
using namespace std;

Exception::Exception() {
	message = "";
}

Exception::Exception(const std::string& msg) : message(msg) { }

Exception::~Exception() throw () { }

const char* Exception::what() const throw () {
	return message.c_str();
}
