#ifndef MGE_GFX_FLOATMAT_H
#define MGE_GFX_FLOATMAT_H

#include <ostream>

namespace mge {
	class FloatVec;

	class FloatMat { // kept in row major
		public:
			inline FloatMat() { } // uninitialized
			FloatMat(const float *data); // initialized
			
			inline float *getData() { return vals; }
			inline const float *getData() const { return vals; }
			
			inline float &operator()(int x, int y) { return vals[x + y*4]; } // row major
			inline float operator()(int x, int y) const { return vals[x + y*4]; }
			inline float &operator[](int pos) { return vals[pos]; }
			inline float operator[](int pos) const { return vals[pos]; }
			
			FloatMat operator*(const FloatMat &mat) const;
			FloatVec operator*(const FloatVec &vec) const;
			
			FloatMat &operator*=(const FloatMat &mat);
			
			FloatMat reciprocal() const;
			FloatMat inverse() const;
			
			bool operator==(const FloatMat &mat) const;
			inline bool operator!=(const FloatMat &mat) const { return !(*this == mat); }
			
			static const FloatMat &identity();
			static const FloatMat translate(float x, float y, float z);
			static const FloatMat scale(float x, float y, float z);
			static const FloatMat rotateZ(float angle); // optimized rotation about Z axis, only one we actually use
	
		private:
			float vals[16];
	};
	
	std::ostream &operator<<(std::ostream &stream, const FloatMat &mat);
}

#endif
