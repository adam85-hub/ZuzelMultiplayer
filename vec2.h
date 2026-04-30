#pragma once
#include <math.h>

namespace Utils {
	struct vec2 {
		vec2(float x, float y) : x(x), y(y) {}
		vec2() : x(0), y(0) {};
		float x, y;


		float Length() const {
			return sqrt(x * x + y * y);
		}

		static float Distance(const vec2& v1, const vec2& v2) {
			return sqrt(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2));
		}

		float Distance(const vec2& other) const {
			return Utils::vec2::Distance(*this, other);
		}

		float Distance(float x, float y) const {
			return sqrt(powf(this->x - x, 2) + powf(this->y - y, 2));
    }

		vec2 operator+(const vec2& other) const {
			return vec2(x + other.x, y+other.y);
		}

		vec2 operator-(const vec2& other) const {
			return vec2(x - other.x, y - other.y);
		}

		vec2 operator*(float scalar) const {
			return vec2(x * scalar, y * scalar);
		}

		float dot(const vec2& other) const {
			return (x * other.x) + (y * other.y);
		}
	};
}