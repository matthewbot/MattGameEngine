#include "ShaderProgram.h"
#include <MGE/gfx/renderer/Renderer.h>
#include "ShaderVariable.h"
#include <MGE/util/Exception.h>
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <sstream>
#include <iostream>

using namespace mge;
using namespace std;

ShaderProgram::ShaderProgram(const ShaderName &name) : name(name) {
	vshaderid = glCreateShader(GL_VERTEX_SHADER);
	pshaderid = glCreateShader(GL_FRAGMENT_SHADER);
	programid = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(programid);
	glDeleteShader(pshaderid);
	glDeleteShader(vshaderid);
	
	for (ShaderVariableMap::iterator i = varcache.begin(); i != varcache.end(); ++i) {
		delete i->second;
	}
}

static char logbuf[1024*8];

string ShaderProgram::getPixelShaderLog() const {
	glGetShaderInfoLog(pshaderid, sizeof(logbuf), NULL, logbuf);
	return string(logbuf);
}

string ShaderProgram::getVertexShaderLog() const {
	glGetShaderInfoLog(vshaderid, sizeof(logbuf), NULL, logbuf);
	return string(logbuf);
}

string ShaderProgram::getProgramLog() const {
	glGetProgramInfoLog(programid, sizeof(logbuf), NULL, logbuf);
	return string(logbuf);
}

string ShaderProgram::getLog() const {
	string pixlog = getPixelShaderLog();
	string vertlog = getVertexShaderLog();
	string proglog = getProgramLog();
	bool first = true;
	stringstream buf;
	
	if (pixlog.length() > 0) {
		buf << "--- Pixel Shader Log ---" << endl;
		buf << pixlog << endl;
		first = false;
	}
	
	if (vertlog.length() > 0) {
		buf << "--- Vertex Shader Log ---" << endl;
		buf << vertlog;
		if (first)
			first = false;
		else
			buf << endl;
	}
	
	if (proglog.length() > 0) {
		buf << "--- Program Log ---" << endl;
		buf << proglog;
		
		if (first)
			first = false;
		else
			buf << endl;
	}
	
	return buf.str();
}

void ShaderProgram::generateTexUniforms(Renderer &renderer) {
	glUseProgram(programid);
	
	for (int i=0; i < MAX_TEXES; i++) {
		stringstream buf;
		buf << "mge_texture" << i;
		
		int uniform = glGetUniformLocation(programid, buf.str().c_str());
		if (uniform != -1) {
			 glUniform1i(uniform, i);
		}
	}
	
	glUseProgram(0);
	renderer.damageShader();
}

const ShaderVariable &ShaderProgram::getVariable(const std::string &name) const {
	ShaderVariableMap::const_iterator i = varcache.find(name);
	if (i != varcache.end())
		return *i->second;
	
	int unifid = glGetUniformLocation(programid, name.c_str());
	if (unifid == -1)
		throw Exception(string("ShaderProgram contains no variable named ") + name);
		
	ShaderVariable *var = new ShaderVariable(programid, unifid, name);
	varcache[name] = var;
	return *var;
}
