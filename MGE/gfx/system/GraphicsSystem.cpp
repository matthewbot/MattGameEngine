#include "GraphicsSystem.h"
#include <MGE/util/Logger.h>
#include <MGE/util/Exception.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <sstream>

using namespace mge;
using namespace std;

GraphicsSystem::GraphicsSystem(Logger &logger, FileStreamProducer &fsp, int w, int h, bool vsync, const std::string &title) 
: subsystem(logger, w, h, vsync, title), timer(), input(w, h), // get SDL and the Timer/WindowInput (SDL input loop) up
  renderer(logger, 4000), rendman(renderer), // get Renderer (OpenGL) and RenderManager up
  texman(logger, fsp, renderer), shade(logger, fsp, renderer), // initialize the TextureManager and the ShaderManager
  display(w, h, rendman) // create the display object
  { }

SystemUpdateValue GraphicsSystem::update() {
	display.update();
	timer.update();
	input.update();
	renderer.clearStats();

	return NONE;
}

const char *GraphicsSystem::getName() const { return "GraphicsSystem"; }

GraphicsSystem::SubSystemHandler::SubSystemHandler(Logger &logger, int w, int h, bool vsync, const std::string &title) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) == -1)
		throw Exception(std::string("Failed to init SDL Video") + SDL_GetError());
		
	SDL_WM_SetCaption(title.c_str(), "");
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, vsync);
	
	if (!SDL_SetVideoMode(w, h, 32, SDL_OPENGL)) {
		stringstream buf;
		buf << "Failed to set video mode " << w << "x" << h << " at 32 bpp: " << SDL_GetError();	
		throw Exception(buf.str());
	}
	
	logger.log("gfx", INFO) << "Created display " << w << "x" << h << endl;
	logger.log("gfx", INFO) << "  GL_VERSION: " << glGetString(GL_VERSION) << endl;
	logger.log("gfx", INFO) << "  GL_RENDERER: " << glGetString(GL_RENDERER) << endl;
}

GraphicsSystem::SubSystemHandler::~SubSystemHandler() {
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
