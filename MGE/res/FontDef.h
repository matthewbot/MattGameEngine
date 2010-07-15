#ifndef MGE_RES_FONTDEF_H
#define MGE_RES_FONTDEF_H

#include <map>

namespace mge {
	struct FontChar {
		typedef char IdType;
		
		IdType id;
		float x, y, width, height;
		float xoffset, yoffset;
		float xadvance;
	};

	struct FontKerning {
		FontChar::IdType first, second;
		float amount;
	};

	struct FontDef {
		int lineheight;
		
		typedef std::map<FontChar::IdType, FontChar> CharMap;
		CharMap chars; // maps character id to FontChar

		typedef std::map<std::pair<FontChar::IdType, FontChar::IdType>, FontKerning> KerningMap;
		KerningMap kernings; // maps a first and second character to a FontKerning
	};
}

#endif
