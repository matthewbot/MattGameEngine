#include "FloatMat.h"
#include "FloatVec.h"
#include <MGE/util/Exception.h>
#include <cmath>
#include <iostream>

using namespace mge;
using namespace std;

FloatMat::FloatMat(const float *data) {
	float *curval = vals;
	for (int i=0; i < 16; i++) {
		*curval++ = *data++;
	}
}

FloatMat FloatMat::operator*(const FloatMat &mat) const {
	FloatMat ret;
	
	for (int outx = 0; outx < 4; outx++) {
		for (int outy = 0; outy < 4; outy++) {
			float sum=0;
			for (int pos = 0; pos < 4; pos++) {
				sum += (*this)(outx, pos) * mat(pos, outy);
			}
			
			ret(outx, outy) = sum;
		}
	}
	
	return ret;
}

FloatVec FloatMat::operator*(const FloatVec &vec) const {
	FloatVec ret;

	for (int outy = 0; outy < 4; outy++) {
		float sum=0;
		for (int pos = 0; pos < 4; pos++) {
			sum += (*this)(pos, outy) * vec[pos];
		}
		
		ret[outy] = sum;
	}
	
	return ret;
}

FloatMat &FloatMat::operator*=(const FloatMat &mat) {
 *this = *this * mat; // TODO: optimize!
 
 return *this;
} 

FloatMat FloatMat::inverse() const {
	FloatMat tmp(*this);
	FloatMat out(FloatMat::identity());

	for (int i = 0; i != 4; i++) {
		float val = tmp(i, i);
		int ind = i;

		for (int j = i + 1; j != 4; j++) {
			if (fabs(tmp(i,j)) > fabs(val)) {
				ind = j;
				val = tmp(i,j);
			}
		}

		if (ind != i) {
			for (int j = 0; j != 4; j++) {
				float t;
				t = out(j,i); out(j,i) = out(j,ind); out(j,ind) = t;
				t = tmp(j,i); tmp(j,i) = tmp(j,ind); tmp(j,ind) = t;
			}
		}

		if (fabs(val) <= 0) {
			throw Exception("No inverse matrix");
		}

		float ival = 1 / val;

		for (int j = 0; j != 4; j++) {
			tmp(j,i) *= ival;
			out(j,i) *= ival;
		}

		for (int j = 0; j != 4; j++) {
			if (j == i)
				continue;

			val = tmp(i,j);

			for (int k = 0; k != 4; k++) {
				tmp(k,j) -= tmp(k,i) * val;
				out(k,j) -= out(k,i) * val;
			}
		}
	}
	
	return out;
}

bool FloatMat::operator==(const FloatMat &mat) const {
	const float *curval = vals;
	const float *matcurval = mat.vals;
	
	for (int i=0; i < 16; i++) {
		if (*curval++ != *matcurval++)
			return false;
	}
	
	return true;
}

const FloatMat &FloatMat::identity() {
	static const float identity_data[16] = {1, 0, 0, 0, 
	                           0, 1, 0, 0, 
	                           0, 0, 1, 0, 
	                           0, 0, 0, 1};
	                           
	static const FloatMat identity(identity_data);
	
	return identity;
}

const FloatMat FloatMat::translate(float x, float y, float z) {
	const float translate_data[16] = {1, 0, 0, x,
	                                  0, 1, 0, y,
	                                  0, 0, 1, z,
	                                  0, 0, 0, 1};

	return FloatMat(translate_data);
}

const FloatMat FloatMat::scale(float x, float y, float z) {
	const float scale_data[16] = {x, 0, 0, 0,
	                              0, y, 0, 0,
	                              0, 0, z, 0,
	                              0, 0, 0, 1};

	return FloatMat(scale_data);
}

const FloatMat FloatMat::rotateZ(float angle) {
	const float cosa = cos(angle);
	const float sina = sin(angle);
	
	const float rotate_data[16] = {cosa, -sina, 0, 0,
	                               sina, cosa , 0, 0,
	                               0   , 0    , 1, 0,
	                               0   , 0    , 0, 1};
	
	return FloatMat(rotate_data);
}

ostream &mge::operator<<(ostream &stream, const FloatMat &mat) {
	for (int y=0; y<4; y++) {
		for (int x=0; x<4; x++) {
			stream << mat(x, y) << " ";
		}
		
		stream << endl;
	}
	
	return stream;
}
