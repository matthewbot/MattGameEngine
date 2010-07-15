#ifndef MGE_GFX_QUAD_H
#define MGE_GFX_QUAD_H

#include "Vertex.h"
#include "PrimitiveBase.h"

namespace mge {
	class Quad : public PrimitiveBase<QUADS, Vertex> {
		public:
			inline Quad() { }
			inline Quad(const Color &color, float x, float y, float w, float h) { setRect(color, x, y, w, h); }
			
			void setRect(const Color &color, float x, float y, float w, float h);
	};
}

#endif
