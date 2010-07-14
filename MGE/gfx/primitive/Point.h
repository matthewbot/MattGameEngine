#ifndef MGE_GFX_POINT_H
#define MGE_GFX_POINT_H

#include "Vertex.h"
#include "PrimitiveBase.h"

namespace mge {
	class Point : public PrimitiveBase<POINTS, Vertex> {
		public:
			inline Point() { }
			inline Point(const Color &col, float x, float y) { set(col, x, y); }
			
			inline void set(const Color &col, float x, float y) { verts[0].set(col, x, y); }
	};
}

#endif
