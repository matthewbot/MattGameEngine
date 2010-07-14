#include "Transform.h"
#include <MGE/util/Vector2D.h>
#include <MGE/gfx/util/FloatVec.h>

using namespace mge;

Transform::Transform() : mat(FloatMat::identity()) { }

Transform& Transform::translate(const Vector2D &vec) {
	mat *= FloatMat::translate(vec.getX(), vec.getY(), 0);
	
	return *this;
}

Transform& Transform::translate(float x, float y) {
	mat *= FloatMat::translate(x, y, 0);
	
	return *this;
}

Transform& Transform::rotate(float rot) {
	mat *= FloatMat::rotateZ(rot);

	return *this;
}

Transform &Transform::scale(const Vector2D &vec) {
	mat *= FloatMat::scale(vec.getX(), vec.getY(), 1);

	return *this;
}

Transform &Transform::scale(float x, float y) {
	mat *= FloatMat::scale(x, y, 1);
	
	return *this;
}

Transform &Transform::invert() {
	mat = mat.inverse();
	
	return *this;
}

Transform &Transform::compose(const Transform &trans) {
	mat *= trans.mat;
	
	return *this;
}

Vector2D Transform::transform(const Vector2D &vec) const {
	FloatVec outvec(mat * vec);
	
	return Vector2D(outvec[0], outvec[1]);
}
