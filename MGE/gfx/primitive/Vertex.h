#ifndef MGE_GFX_VERTEX_H
#define MGE_GFX_VERTEX_H

#include <MGE/gfx/util/Color.h>

namespace mge {	
	struct Pt {
		float x, y;
		
		inline void set(float x, float y) { this->x = x; this->y = y; }
	};

	struct Vertex {
		Color col;
		Pt pos;
		
		inline void set(const Color &col, float x, float y) { this->col = col; pos.set(x, y); }
	};
	
	struct TexVertex {
		Color col;
		Pt pos;
		Pt tex;
		
		inline void set(const Color &col, float x, float y, float tx, float ty) { this->col = col; pos.set(x, y); tex.set(tx, ty); }
	};
	
	template <int texcount> struct MultiTexVertex {
		Color col;
		Pt pos;
		Pt texes[texcount];
		
		inline void set(const Color &col, float x, float y) { this->col = col; pos.set(x, y); }
	};
}

#endif
