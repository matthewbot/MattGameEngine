#include "Line.h"
#include <MGE/gfx/Viewport.h>

using namespace mge;

void Line::set(const Color &color, float x, float y, float x2, float y2) {
	verts[0].set(color, x, y);
	verts[1].set(color, x2, y2);
}

void Line::drawRect(Viewport &vp, float x, float y, float w, float h, const Color &color) {
	vp.render(Line(color, x, y, x, y+h));
	vp.render(Line(color, x, y+h, x+w, y+h));
	vp.render(Line(color, x+w, y+h, x+w, y));
	vp.render(Line(color, x+w, y, x, y));
}
