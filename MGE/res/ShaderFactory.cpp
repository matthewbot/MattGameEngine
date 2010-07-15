#include "ShaderFactory.h"
#include "Shader.h"
#include <MGE/res/system/ResourceNode.h>
#include <MGE/gfx/shader/ShaderManager.h>

using namespace mge;
using namespace std;

ShaderFactory::ShaderFactory(ShaderManager &shademan) : shademan(shademan) { }

Resource *ShaderFactory::makeResource(const std::string &name, const ResourceNode &props) {
	if (props.getString("type") != "shader")
		return NULL;

	string pixshader = props.getString("pixshader");
	string vertshader = props.getString("vertshader");
	
	return new Shader(name, shademan.getProgram(ShaderName(pixshader, vertshader)));
}

