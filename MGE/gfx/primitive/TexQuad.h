#ifndef MGE_GFX_TEXQUAD_H
#define MGE_GFX_TEXQUAD_H

#include "Vertex.h"
#include "PrimitiveBase.h"

namespace mge {
	class Color;

	class TexQuad : public PrimitiveBase<QUADS, TexVertex> {
		public:
			inline TexQuad() { }
			inline TexQuad(const Color &color, float x, float y, float tx, float ty, float w, float h) { setRect(color, x, y, tx, ty, w, h); }
			
			void setRect(const Color &color, float x, float y, float tx, float ty, float w, float h);
	};
}

#endif
