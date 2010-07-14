#include "TexQuad.h"

using namespace mge;

void TexQuad::setRect(const Color &color, float x, float y, float tx, float ty, float w, float h) {
	verts[0].set(color, x,y+h, tx,ty);
	verts[1].set(color, x+w,y+h, tx+w,ty);
	verts[2].set(color, x+w,y, tx+w,ty+h);
	verts[3].set(color, x,y, tx,ty+h);	
}
