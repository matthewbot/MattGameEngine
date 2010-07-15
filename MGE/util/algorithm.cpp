#include "algorithm.h"
#include <algorithm>
#include <cctype>

using namespace mge;
using namespace std;

vector<string> mge::str_split(char c, const string &str) {
	vector<string> ret;
	
	for (size_t prevpos=0, curpos=0; (curpos = str.find(c, prevpos)) != string::npos; prevpos = curpos+1) {
		ret.push_back(str.substr(prevpos, curpos-prevpos));
	}
	
	return ret;
}

string mge::str_tolower(const string &str) {
	string lower(str.size(), ' ');
	
	transform(lower.begin(), lower.end(), lower.begin(), (int(*)(int))std::tolower); // C++ is such a beautiful language....
	
	return lower;
}
