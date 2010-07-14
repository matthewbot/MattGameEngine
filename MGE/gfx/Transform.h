#ifndef MGE_GFX_TRANSFORM_H
#define MGE_GFX_TRANSFORM_H

#include <MGE/gfx/util/FloatMat.h>

namespace mge {
	class Vector2D;

	class Transform {
		public:
			Transform();
        
      inline FloatMat &getMat() { return mat; }
      inline const FloatMat &getMat() const { return mat; }
      
			Transform &translate(const Vector2D &vec);
			Transform &translate(float x, float y);
			Transform &rotate(float rot);
			Transform &scale(const Vector2D &vec);
			Transform &scale(float x, float y);
			Transform &compose(const Transform &transform);
			Transform &invert();
			
			Vector2D transform(const Vector2D &vec) const;
	      
			inline bool operator ==(const Transform &trans) const { return mat == trans.mat; }
			inline bool operator !=(const Transform &trans) const { return mat != trans.mat; }

		private:
			FloatMat mat;
	};
}

#endif
