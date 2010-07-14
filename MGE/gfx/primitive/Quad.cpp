#include "Quad.h"

using namespace mge;

void Quad::setRect(const Color &color, float x, float y, float w, float h) {
	verts[0].set(color, x, y);
	verts[1].set(color, x+w, y);
	verts[2].set(color, x+w, y+h);
	verts[3].set(color, x, y+h);
}
