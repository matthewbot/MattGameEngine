#include "Renderer.h"
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/shader/ShaderProgram.h>
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/shader/ShaderVariable.h>
#include <MGE/gfx/util.h>
#include <MGE/gfx/ViewSection.h>
#include <MGE/gfx/Transform.h>
#include <MGE/util/Exception.h>
#include <MGE/util/Logger.h>
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace mge;
using namespace std;

Renderer::Renderer(Logger &logger, int bufsize) : buf(new float [bufsize]), bufsize(bufsize) {
	clearStats();

	GLenum result = glewInit(); // initialize GLEW
	if (result != GLEW_OK)
		throw Exception(string("Failed to init GLEW: ") + string((const char *)glewGetErrorString(result)));	
	logger.log("gfx", DEBUG) << "Initialized GLEW" << endl;
	/*if (!GLEW_VERSION_2_1)
		throw Exception("This game requires a graphics card supporting OpenGL 2.1. Sorry!");*/ // TODO: This doesn't work under linux
	
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &texunits); // initialize texture units
	if (texunits > MAX_TEXES)
		texunits = MAX_TEXES;
	logger.log("gfx", DEBUG) << "Initializing " << texunits << " texture units" << endl;
		
	for (int i=0; i < texunits; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glEnable(GL_TEXTURE_2D);
	}

	glEnable(GL_BLEND); // global opengl state
	glEnable(GL_SCISSOR_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glColorPointer(4, GL_FLOAT, 6*4, &buf[0]);
	glVertexPointer(2, GL_FLOAT, 6*4, &buf[4]);
	
	clearBuf();
}

bool Renderer::appendBuf(const Primitive &prim) { 
	const PrimitiveProperties &props = prim.getProps();

	if (bufsize - (bufpos - &buf[0]) < props.datacount) // verify it will fit
		return false; // if not, fail to append

	const float *databegin = prim.dataBegin();							
  bufpos = std::copy(databegin, databegin+props.datacount, bufpos);
  vertcount += props.vertcount;
  return true;
}

void Renderer::clearBuf() {
	bufpos = &buf[0];
	vertcount = 0;
}

void Renderer::setViewport(const ViewSection &viewport) {
	glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport.w, 0, viewport.h, -1, 1);;
}

void Renderer::setState(const RenderState &state, const Transform &trans, const ViewSection &clip) {
	// step 1 -- clip
	glScissor(clip.x, clip.y, clip.w, clip.h);
	
	// step 2 -- transform
	glMatrixMode(GL_MODELVIEW);
	glLoadTransposeMatrixf(trans.getMat().getData());
	
	// step 3 -- Count textures
	int texcount = 0;
	for (int i=0; i < MAX_TEXES; i++) {
		if (state.getTexture(i)) {
			if (texcount < i)
				throw Exception("Unsupported RenderState configuration: unused texture unit in-between two used texture units");
			texcount++;
		}
	}
	
	if (texcount > texunits) {
		stringstream buf;
		buf << "Not enough texture units " << texunits << " for textures specified in RenderState " << texcount;
		throw Exception(buf.str());
	}
	
	// step 4 -- Color/vertex pointers
	int stride = (6 + 2*texcount)*4;
	
	glColorPointer(4, GL_FLOAT, stride, &buf[0]);
	glVertexPointer(2, GL_FLOAT, stride, &buf[4]);
	
	// step 5 -- Texture/texture pointer settings
	glMatrixMode(GL_TEXTURE);
	
	for (int i=0; i < texunits; i++) {
		const boost::shared_ptr<Texture> &tex = state.getTexture(i);
		if (prevtexes[i].lock() == tex) // optimization, if the same texture as requested was previously set in the same slot, don't have to set it again
			continue; // this is safe, because if a Texture gets deleted, the weak pointer will break, and OpenGL will automatically unbind it, so the cache is still consistent
			
		glActiveTexture(GL_TEXTURE0 + i);
		glClientActiveTexture(GL_TEXTURE0 + i);
		
		if (tex) {
			glBindTexture(GL_TEXTURE_2D, tex->getID());
			
			glLoadIdentity(); // we are still in GL_TEXTURE mode
			glScalef((float)1/tex->getInternalWidth(), (float)1/tex->getInternalHeight(), 0);

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, stride, &buf[6 + (i*2)]);
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
			
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		prevtexes[i] = tex;
	}
	
	// step 6 -- program settings
	
	if (state.getProgram()) {
		glUseProgram(state.getProgram()->getID());
		
		for (RenderState::ProgramVariableIterator i = state.beginPVars(); i != state.endPVars(); ++i) {
			const ShaderVariable &var = *i->first;
			const ShaderVariableValue &val = i->second;
			
			int id = var.getUniformID();
			switch (val.getCount()) {
				case 1:
					glUniform1f(id, val[0]);
					break;
					
				case 2:
					glUniform2f(id, val[0], val[1]);
					break;
					
				case 3:
					glUniform3f(id, val[0], val[1], val[2]);
					break;
					
				case 4:
					glUniform4f(id, val[0], val[1], val[2], val[3]);
					break;
			}
		}
	} else
		glUseProgram(0);
		
	// step 7 -- other settings
	glPointSize(state.getPointSize());
}

void Renderer::drawBuf(PrimitiveType type) {
	int gltype=0;
	
	switch (type) {
		case POINTS:
			gltype = GL_POINTS;
			break;
			
		case LINES:
			gltype = GL_LINES;
			break;
			
		case QUADS:
			gltype = GL_QUADS;
			break;
	}
	
	glDrawArrays(gltype, 0, vertcount);
	
	stats.batches++;
	stats.verts += vertcount;
}

void Renderer::drawClear(const Color &col) {
	glDisable(GL_SCISSOR_TEST);
	glClearColor(col.r, col.g, col.b, col.a); 
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_SCISSOR_TEST);
}

void Renderer::damageTexture() {
	for (int i=0; i < texunits; i++) {
		prevtexes[i].reset();
	}
}

void Renderer::damageShader() {
	// TODO cache shader
}

void Renderer::clearStats() {
	stats.verts = stats.batches = 0;
}
