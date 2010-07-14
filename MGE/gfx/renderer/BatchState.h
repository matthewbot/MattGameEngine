#ifndef MGE_GFX_BATCHSTATE_H
#define MGE_GFX_BATCHSTATE_H

#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/Transform.h>
#include <MGE/gfx/ViewSection.h>
#include <MGE/gfx/primitive/Primitive.h> // for PrimitiveType
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mge {
	class RenderRootCallback;

	class BatchState {
		public:
			BatchState();
			BatchState(PrimitiveType type, const boost::shared_ptr<RenderRootCallback> callback, const RenderState &state, const Transform &trans, const ViewSection &clip);
			~BatchState();
			
			void clear();
			
			bool operator==(const BatchState &bstate) const;
			inline bool operator!=(const BatchState &bstate) const { return !(*this == bstate); }
		
			inline PrimitiveType getType() const { return type; }
			inline boost::shared_ptr<RenderRootCallback> getCallback() const { return callback.lock(); }
			inline const RenderState &getRenderState() const { return state; }
			inline const Transform &getTransform() const { return trans; }
			inline const ViewSection &getClip() const { return clip; }
		
		private:
			PrimitiveType type;
			boost::weak_ptr<RenderRootCallback> callback;
			RenderState state;
			Transform trans;
			ViewSection clip;
	};
}

#endif
