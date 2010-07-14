#include "Font.h"
#include "FontDef.h"
#include "FontDefReader.h"
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/primitive/TexQuad.h>
#include <MGE/gfx/Viewport.h>
#include <cmath>

using namespace std;
using namespace mge;
using namespace boost;

Font::Font(auto_ptr<FontDef> &def, const shared_ptr<Texture> &tex, const string &name) : Resource(name), tex(tex), def(def) { }

int Font::getLineHeight() {
	return def->lineheight;
}

int Font::getWidth(const string &str) {
	float width=0;

	for (FontDefReader reader(*def, str); reader; ++reader) { // go through every character, looking stuff up
		if (reader->hasKerning())
			width += reader->getKerning();

		width += reader->getChar().xadvance;
	}

	return (int)ceil(width);
}

float Font::render(const Viewport &out, float xpos, float ypos, const string &str, const Color &col, const Transform &trans) {
	RenderState state;
	state.texture(tex);

	ypos += def->lineheight;

	for (FontDefReader reader(*def, str); reader; ++reader) { // go through every character, looking up stuff from the FontDef
		if (reader->hasKerning()) // if we got kerning data for this
			xpos += reader->getKerning(); // adjust xpos

		const FontChar &ch = reader->getChar();

		if (reader->getCharValue() != ' ') { // as long as its not a space
			float x = xpos + ch.xoffset; // build a quad from the character data
			float y = ypos - ch.yoffset - ch.height;
			float tx = ch.x;
			float ty = ch.y;
			float w = ch.width;
			float h = ch.height;
	
			TexQuad tquad(col, x, y, tx, ty, w, h);
			out.render(state, trans, tquad);;
		}

		xpos += ch.xadvance;
	}

	return xpos;
}

