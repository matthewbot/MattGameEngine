#ifndef MGE_UTIL_H_
#define MGE_UTIL_H_

#include <exception>
#include <string>

namespace mge {
	class Exception : public std::exception {
		public:
			Exception();
			Exception(const std::string& msg);
			virtual ~Exception() throw ();
			
			virtual const char* what() const throw ();
		private:
			std::string message;
	};
}

#endif /*MGE_UTIL_H_*/
