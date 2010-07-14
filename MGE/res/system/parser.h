#ifndef MGE_RES_PARSER_H
#define MGE_RES_PARSER_H

#include <utility>
#include <vector>
#include <string>
#include <istream>
namespace mge {
	class ResourceNode;

	std::pair<ResourceNode, std::vector<std::string> > parseResourceFile(std::istream &stream); // parser is written in a functional style
}

#endif
