#ifndef MGE_GFX_RENDERER_H
#define MGE_GFX_RENDERER_H

#include "RenderStats.h"
#include <boost/noncopyable.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <vector>
#include <MGE/gfx/primitive/Primitive.h>
#include <MGE/gfx/util.h>
#include <ostream>

// This is the central wrapper around OpenGL. It converts MGE state objects
// into OpenGL state, and holds the float buffer used for rendering.

namespace mge {
	class Texture;
	class Logger;
	class RenderState;
	class ViewSection;
	class Primitive;
	class Transform;
	struct Color;

	class Renderer : boost::noncopyable {
		public:
			Renderer(Logger &logger, int bufsize);
			
			bool appendBuf(const Primitive &prim);
			void clearBuf();
			
			void setViewport(const ViewSection &viewport);
			void setState(const RenderState &state, const Transform &trans, const ViewSection &clip); // TODO: don't need Transform, just the FloatMat
			
			void drawBuf(PrimitiveType type);
			void drawClear(const Color &color);
			
			void damageTexture();
			void damageShader();
			
			inline const RenderStats &getStats() const { return stats; }
			void clearStats();
			
		private:
			boost::scoped_array<float> buf; // this is the shared buffer that we assemble vertex arrays in
			int bufsize; float *bufpos; // info about buffer
			int vertcount;
			
			boost::weak_ptr<Texture> prevtexes[MAX_TEXES]; // weak, because we're just caching the previous texture to remove redundant state changes. Don't actually need it
			
			int texunits; // total number of texture units we have available
			
			RenderStats stats;
	};
}

#endif
