#include "ShaderName.h"

using namespace mge;
using namespace std;

ShaderName::ShaderName(const std::string &pixshader, const std::string &vertshader)
: pixshader(pixshader), vertshader(vertshader) { }

bool ShaderName::operator==(const ShaderName &other) const {
	return pixshader == other.pixshader && vertshader == other.vertshader;
}

bool ShaderName::operator<(const ShaderName &other) const {
	int cmp = pixshader.compare(other.pixshader);
	
	if (cmp < 0)
		return true;
	else if (cmp > 0)
		return false;
		
	cmp = vertshader.compare(other.vertshader);
	
	if (cmp < 0)
		return true;
	else
		return false;
}

std::ostream &mge::operator<<(std::ostream &stream, const ShaderName &name) {
	return stream << "(" << name.getPixelShader() << "|" << name.getVertexShader() << ")";
}	
