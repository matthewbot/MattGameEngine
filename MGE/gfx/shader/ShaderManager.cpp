#include "ShaderManager.h"
#include <MGE/util/Exception.h>
#include <MGE/util/FileStreamProducer.h>
#include <MGE/util/Logger.h>
#include <boost/scoped_array.hpp>
#include <GL/glew.h>
#include <sstream>
#include <memory>

using namespace mge;
using namespace std;
using namespace boost;

ShaderManager::ShaderManager(Logger &logger, FileStreamProducer &fsp, Renderer &renderer) 
: logger(logger), fsp(fsp), renderer(renderer) { }

shared_ptr<ShaderProgram> ShaderManager::getProgram(const ShaderName &name) {
	ShaderCache::iterator i = shadercache.find(name);
	if (i != shadercache.end()) {
		shared_ptr<ShaderProgram> shader(i->second.lock());
		if (shader)
			return shader;
	}
		
	shared_ptr<ShaderProgram> shader(new ShaderProgram(name)); // use our deleter functor object
	bool vert_compiled = compileShader(shader->vshaderid, name.getVertexShader());
	bool pix_compiled = compileShader(shader->pshaderid, name.getPixelShader());
	bool prog_linked;
	
	if (vert_compiled && pix_compiled) { // if everything compiled
		GLint progid = shader->programid;
		
		glAttachShader(progid, shader->vshaderid); // link it
		glAttachShader(progid, shader->pshaderid);
		glLinkProgram(progid);
		
		GLint linked;
		glGetProgramiv(progid, GL_LINK_STATUS, &linked); // pull the result of the link
		
		prog_linked = (linked == GL_TRUE);
	} else // something didn't compile
		prog_linked = false;
		
	if (!(vert_compiled && pix_compiled && prog_linked)) { // if everything turned out ok
		// Something didn't work out so good, so now we prepare an exception
		stringstream buf;
		buf << "Failed to make shader program " << name << endl;
		buf << "State: vert_compiled " << vert_compiled << " pix_compiled " << pix_compiled << " prog_linked " << prog_linked << endl;
		buf << "Complete shader log: " << endl << endl;
		buf << shader->getLog() << endl;
	
		throw Exception(buf.str());
	}
		
	shader->generateTexUniforms(renderer); // lookup mge_texturex uniforms
	
	logger.log("gfx", DEBUG) << "Compiled shader " << name << endl;
	string log = shader->getLog();
	if (log.length() > 0) {
		logger.log("gfx", DEBUG) << "Logs: " << endl << shader->getLog() << endl;
		logger.log("gfx", DEBUG) << "End log for " << name << endl;
	}
	
	return shader; // release the shader into the wild!	
}


bool ShaderManager::compileShader(int id, const string &filename) {
	{
		auto_ptr<istream> stream(fsp.readFile(filename)); // open stream
		stream->seekg(0, ios::end); // position at end
		
		GLint length = stream->tellg(); // get length
		scoped_array<GLchar> buffer(new GLchar [length]); // allocate a buffer, hold in scoped_array
	
		stream->seekg(0, ios::beg); // position at beginning
		stream->read(buffer.get(), length); // and read into buffer

		const GLchar *bufptr = buffer.get(); // OpenGL needs a pointer to a pointer
		glShaderSource(id, 1, &bufptr, &length); // upload source to OpenGL
	} // let buffer and stream go out of scope and be deleted
	
	glCompileShader(id); // compile shader
	
	GLint compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled); // pull back the compile result

	return compiled == GL_TRUE; // and return it
}
