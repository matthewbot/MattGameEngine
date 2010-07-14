#ifndef MGE_UTIL_ALGO_H_
#define MGE_UTIL_ALGO_H_

#include <string>
#include <vector>

namespace mge {
	std::vector<std::string> str_split(char c, const std::string &str);
	std::string str_tolower(const std::string &str);
}

#endif
