#include "FloatVec.h"
#include <MGE/util/Vector2D.h>

using namespace mge;

FloatVec::FloatVec(const Vector2D &vec) {
	vals[0] = vec.getX();
	vals[1] = vec.getY();
	vals[2] = 0;
	vals[3] = 1;
}

FloatVec::FloatVec(const float *data) {
	float *val = vals;
	for (int i=0; i<4; i++) {
		*val++ = *data++;
	}
}

bool FloatVec::operator==(const FloatVec &vec) const {
	const float *val = vals;
	const float *vecval = vec.vals;
	
	for (int i=0; i<4; i++) {
		if (*val++ != *vecval++)
			return false;
	}
	
	return true;
}
