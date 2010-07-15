#include <MGE/util/Vector2D.h>
#include <cmath>

using namespace mge;
using namespace std;

Vector2D::Vector2D() : x(0), y(0) { }
Vector2D::Vector2D(float x, float y) : x(x), y(y) { }

const Vector2D Vector2D::fromAngle(float angle, float mag) {
	return Vector2D(cos(angle)*mag, sin(angle)*mag);
}

float Vector2D::getAngle() const { return atan2(y, x); }
float Vector2D::getMagnitude() const { return sqrt(x*x + y*y); }

void Vector2D::setAngle(float angle) {
	float mag = getMagnitude();
	x = mag*cos(angle);
	y = mag*sin(angle);
}

void Vector2D::setMagnitude(float mag) {
	float angle = getAngle();
	x = mag*cos(angle);
	y = mag*sin(angle);
}

Vector2D &Vector2D::operator+=(const Vector2D &vec) {
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2D &Vector2D::operator-=(const Vector2D &vec) {
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2D &Vector2D::operator*=(float c) {
	x *= c;
	y *= c;
	return *this;
}

Vector2D &Vector2D::operator/=(float c) {
	x /= c;
	y /= c;
	return *this;
}

const Vector2D Vector2D::operator+(const Vector2D &vec) const {
	return Vector2D(*this) += vec;
}

const Vector2D Vector2D::operator-(const Vector2D &vec) const {
	return Vector2D(*this) -= vec;
}

const Vector2D Vector2D::operator*(float c) const {
	return Vector2D(*this) *= c;
}

const Vector2D Vector2D::operator/(float c) const {
	return Vector2D(*this) /= c;
}

bool Vector2D::operator==(const Vector2D &vec) const {
	return (x == vec.x) && (y == vec.y);
}

bool Vector2D::operator!=(const Vector2D &vec) const {
	return !(*this == vec);
}
