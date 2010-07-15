#ifndef MGE_GFX_RENDERROOT_H
#define MGE_GFX_RENDERROOT_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <MGE/gfx/util/Color.h>

// A RenderRoot is the parent class of anything that can be rendered to.
// Subclasses differentiate the RenderRoot by providing a RenderRootCallback.
// The RenderRootCallback is called from within the RenderManager to configure the Renderer
// specifically for the RenderRoot.

namespace mge {
	class RenderManager;
	class RenderRootCallback;
	class RenderState;
	class Transform;
	class ViewSection;
	class Primitive;
	class Renderer;

	class RenderRoot : boost::noncopyable {
		public:
			RenderRoot(int width, int height, RenderManager &rendman, RenderRootCallback *callback);
		
			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }
		
			void render(const RenderState &state, const Transform &transform, const ViewSection &clip, const Primitive &primitive) const;	
			void clear(const Color &color = Color::BLACK) const; // clears to this color

			void flush() const;
			
		private:		
			bool isCurrentTarget();
		
			int width, height;
			RenderManager &rendman;
			boost::shared_ptr<RenderRootCallback> callback;
	};
}

#endif
