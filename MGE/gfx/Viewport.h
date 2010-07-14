#ifndef MGE_GFX_Viewport_H
#define MGE_GFX_Viewport_H

#include "Transform.h"
#include "ViewSection.h"

// A Viewport consists of a RenderRoot, a Transform, and a ViewSection.
// It is used to render primitives to a RenderRoot with a transformation and clipping.

namespace mge {
	class RenderRoot;
	class Primitive;
	class Vector2D;
	class RenderState;

	class Viewport {
		public:
			Viewport(RenderRoot &root); // creates a viewport rendering to root
			Viewport(const Viewport &view, const ViewSection &viewclip); // clones a viewport, this time with clipping. Clip is specified in view coords
			Viewport(const Viewport &view, const Transform &trans);
			
			inline const Transform &getTransform() const { return trans; }
			inline Transform &getTransform() { return trans; }
			inline const ViewSection &getRootClip() const { return rootclip; } 
			inline ViewSection &getRootClip() { return rootclip; }
			inline const RenderRoot &getRoot() const { return *root; } 
			
			bool contains(const Vector2D &pos) const;
			bool contains(const Vector2D &pos, const Transform &trans) const;
			bool contains(float x, float y) const;
			bool contains(float x, float y, const Transform &trans) const;
		
			void render(const Primitive &prim) const;
			void render(const RenderState &state, const Primitive &prim) const;
			void render(const RenderState &state, const Transform &trans, const Primitive &prim) const;
			void renderPrecmp(const RenderState &state, const Transform &precmptrans, const Primitive &prim) const;
			
		private:
			Viewport(); // can't create an empty viewport
			
			void genRootClip();
		
			Transform trans;
			const RenderRoot *const root;
			ViewSection rootclip;
	};
}

#endif
