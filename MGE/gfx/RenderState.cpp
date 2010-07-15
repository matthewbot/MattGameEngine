#include "RenderState.h"
#include <MGE/gfx/shader/ShaderProgram.h>
#include <MGE/gfx/shader/ShaderVariable.h>
#include <MGE/util/Exception.h>

using namespace mge;
using namespace boost;

RenderState::RenderState() : pointsize(1) { }

RenderState& RenderState::program(const shared_ptr<ShaderProgram> &prgm) {
	if (this->prgm != prgm) {
		prgmvars.clear();
		this->prgm = prgm;
	}
	
	return *this;
}

RenderState& RenderState::programVar(const std::string &name, const ShaderVariableValue &value) {
	if (!prgm)
		throw Exception("Setting programVar on a RenderState with no program!");
		
	prgmvars[&prgm->getVariable(name)] = value;	
	
	return *this;
}

RenderState& RenderState::texture(const shared_ptr<Texture> &tex, int id) {
	texes[id] = tex;
	
	return *this;
}

RenderState& RenderState::clearTexture(int id) {
	texes[id].reset();
	
	return *this;
}

RenderState& RenderState::pointSize(float pointsize) {
	this->pointsize = pointsize;
	
	return *this;
}

bool RenderState::operator==(const RenderState &state) const {
	for (int i=0; i < MAX_TEXES; i++) {
		if (!(texes[i] == state.texes[i]))
			return false;
	}
	
	if (!(prgm == state.prgm))
		return false;
		
	if (!(prgmvars == state.prgmvars))
		return false;
			
	if (!(pointsize == state.pointsize))
		return false;

	return true;
}
