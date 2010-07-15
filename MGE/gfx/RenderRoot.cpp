#include "RenderRoot.h"
#include <MGE/gfx/renderer/RenderRootCallback.h>
#include <MGE/gfx/renderer/RenderManager.h>

using namespace std;
using namespace mge;

RenderRoot::RenderRoot(int width, int height, RenderManager &rendman, RenderRootCallback *callback) 
: width(width), height(height), rendman(rendman), callback(callback) { }

void RenderRoot::render(const RenderState &state, const Transform &transform, const ViewSection &clip, const Primitive &primitive) const {
	rendman.render(callback, state, transform, clip, primitive);
}

void RenderRoot::clear(const Color &color) const {
	rendman.clear(callback, color);
}

void RenderRoot::flush() const {
	rendman.flush(); // TODO Pass our callback, only flush if its truly us
}
		
