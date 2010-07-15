#include "Sprite.h"
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/primitive/TexQuad.h>
#include <MGE/gfx/Viewport.h>

using namespace std;
using namespace mge;
using namespace boost;

Sprite::Sprite(const string &name, shared_ptr<Texture> tex, const SpriteProps &props) : Resource(name), tex(tex), props(props) { }

void Sprite::render(const Viewport &out, float x, float y) {
	renderRotated(out, x, y, 0);
}

void Sprite::renderRotated(const Viewport &out, float x, float y, float rot) {
	float xo = -props.ox, yo = -props.oy;
	TexQuad tquad; RenderState state; Transform trans;
	
	tquad.setRect(Color::WHITE, xo, yo, props.tx, props.ty, props.tw, props.th);
	state.texture(tex);
	trans.rotate(rot + props.rotoffset).translate(x, y);
	
	out.render(state, trans, tquad);
}
void Sprite::renderTiled(const Viewport &out, float xpos, float ypos, int xcount, int ycount) {
	for (int xoff=0; xoff < xcount; xoff++) {
		for (int yoff=0; yoff < ycount; yoff++) {
			render(out, xpos + xoff*props.tw, ypos + yoff*props.th);
		}
	}
}
