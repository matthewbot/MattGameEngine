#ifndef MGE_GFX_FLOATVEC_H
#define MGE_GFX_FLOATVEC_H

namespace mge {
	class Vector2D;

	class FloatVec {
		public:
			inline FloatVec() { } // unitialized
			FloatVec(const Vector2D &vec);
			FloatVec(const float *data);
			
			inline const float *getData() const { return vals; }
			inline float *getData() { return vals; }
			inline float &operator[](int pos) { return vals[pos]; }
			inline float operator[](int pos) const { return vals[pos]; }
			
			bool operator==(const FloatVec &vec) const;
			inline bool operator!=(const FloatVec &vec) const { return !(*this == vec); }
			
		private:
			float vals[4];
	};
}


#endif
