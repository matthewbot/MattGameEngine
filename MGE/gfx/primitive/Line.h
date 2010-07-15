#ifndef MGE_GFX_LINE_H
#define MGE_GFX_LINE_H

#include "Vertex.h"
#include "PrimitiveBase.h"

namespace mge {
	class Viewport;
	class Color;

	class Line : public PrimitiveBase<LINES, Vertex> {
		public:
			inline Line() { }
			inline Line(const Color &color, float x, float y, float x2, float y2) { set(color, x, y, x2, y2); }
			
			void set(const Color &color, float x, float y, float x2, float y2);
			
			static void drawRect(Viewport &vp, float x, float y, float w, float h, const Color &col=Color::WHITE);
	};
}

#endif
