#ifndef MGE_GFX_MULTITEXQUAD_H
#define MGE_GFX_MULTITEXQUAD_H

#include "Vertex.h"
#include "PrimitiveBase.h"

namespace mge {
	template <int texcount> class MultiTexQuad : public PrimitiveBase<QUADS, MultiTexVertex<texcount> > {
		public:
			typedef MultiTexVertex<texcount> VertexType;
		
			inline MultiTexQuad() { }
			inline MultiTexQuad(const Color &color, float x, float y, float w, float h) {
				setRect(color, x, y, w, h);
			}
			
			void setRect(const Color &color, float x, float y, float w, float h) {
				verts[0].set(color, x, y+h);
				verts[1].set(color, x+w, y+h);
				verts[2].set(color, x+w, y);
				verts[3].set(color, x, y);
			}
			
			void cloneTexes(int srctex, int dsttex) {
				for (int i=0; i < 4; i++) {
					verts[i].texes[dsttex].x = verts[i].texes[srctex].x;
					verts[i].texes[dsttex].y = verts[i].texes[srctex].y;
				}
			}
			
		private:
			using PrimitiveBase<QUADS, MultiTexVertex<texcount> >::verts;
	};
}

#endif
