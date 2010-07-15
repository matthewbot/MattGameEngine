#include "Display.h"
#include <MGE/gfx/renderer/Renderer.h>
#include <MGE/gfx/renderer/RenderRootCallback.h>
#include <MGE/gfx/ViewSection.h>
#include <MGE/util/Exception.h>
#include <SDL/SDL.h>
#include <sstream>

using namespace std;
using namespace mge;
using namespace boost;

namespace {
	struct DisplayCallback : public RenderRootCallback {	
		const Display &disp;
		
		DisplayCallback(const Display &disp) : disp(disp) { }
		virtual void prepareRenderer(Renderer &renderer) {
			// placeholder: clear any FBO
			ViewSection view;
			view.x = view.y = 0;
			view.w = disp.getWidth(); view.h = disp.getHeight();
			renderer.setViewport(view);
		}
	};
}

Display::Display(int w, int h, RenderManager &rendman) : RenderRoot(w, h, rendman, new DisplayCallback(*this)) { }

Display::~Display() { }

void Display::update() {
	flush();
	SDL_GL_SwapBuffers();
}
