#ifndef MGE_UTIL_VECTOR_H
#define MGE_UTIL_VECTOR_H

namespace mge {
	const float PI = 3.1415926535f;

	class Vector2D {
		public:
			Vector2D();
			Vector2D(float x, float y);

			static const Vector2D fromAngle(float angle, float mag);

			const Vector2D operator*(float c) const;
			const Vector2D operator/(float c) const;
			const Vector2D operator+(const Vector2D &vec) const;
			const Vector2D operator-(const Vector2D &vec) const;
			const Vector2D operator-() const;

			Vector2D &operator*=(float c);
			Vector2D &operator/=(float c);
			Vector2D &operator+=(const Vector2D &vec);
			Vector2D &operator-=(const Vector2D &vec);

			bool operator==(const Vector2D &vec) const;
			bool operator!=(const Vector2D &vec) const;

			inline const float &getX() const { return x; }
			inline const float &getY() const { return y; }
			inline float &getX() { return x; }
			inline float &getY() { return y; }
			float getAngle() const;
			float getMagnitude() const;
			
			inline void setX(float x) { this->x = x; }
			inline void setY(float y) { this->y = y; }
			void setAngle(float angle);
			void setMagnitude(float magnitude);

		private:
			float x, y;
	};
}

#endif
