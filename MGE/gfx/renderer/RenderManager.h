#ifndef MGE_GFX_RENDEROPMANAGER_H
#define MGE_GFX_RENDEROPMANAGER_H

#include "BatchState.h"
#include <MGE/gfx/util/Color.h>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

// RenderManager is a class that exists within the GraphicsSystem.
// There is only one, and is shared by all RenderTargets.
// It is used as a wrapper around the Renderer, and builds batches
// inside the Renderer's buffer where possible

// target1.render(something)
// target1.render(something) // batched onto first command
// target2.render(something) // different target, must flush the batch formed from target1
// target2.render(differentprimitive) // different primitive/render op, must flush the batch again

namespace mge {
	class RenderRootCallback;
	class Renderer;
	class Primitive;
	class RenderStats;
	
	class RenderManager : boost::noncopyable {
		public:
			RenderManager(Renderer &renderer);
			~RenderManager();
			
			void render(const boost::shared_ptr<RenderRootCallback> &callback, const RenderState &state, const Transform &trans, const ViewSection &clip, const Primitive &prim);
			void clear(const boost::shared_ptr<RenderRootCallback> &callback, const Color &color);
			void flush();
			
			inline bool hasBatch() const { return hasbatch; }
			
			const RenderStats &getStats() const;
			
		private:
			Renderer &renderer;
		
			bool hasbatch;
			BatchState batchstate;

			void setBatch(const BatchState &batchstate);
			void appendBatch(const Primitive &prim);
			void renderBatch();
			void clearBatch();
	};
}

#endif
