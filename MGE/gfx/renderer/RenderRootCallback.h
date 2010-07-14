#ifndef MGE_GFX_RENDERROOTCALLBACK_H
#define MGE_GFX_RENDERROOTCALLBACK_H

namespace mge {
	class Renderer;

	class RenderRootCallback {
		public:
			virtual void prepareRenderer(Renderer &renderer) = 0;
			virtual inline ~RenderRootCallback() { }
	};
}

#endif
