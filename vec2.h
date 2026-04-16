#pragma once
#include <cmath>

namespace Utils {
	struct vec2 {
		vec2(float x, float y) : x(x), y(y) {}
		vec2() : x(0), y(0) {};
		float x, y;

		static float Distance(const vec2& v1, const vec2& v2) {
			return std::sqrt(std::powf(v1.x - v2.x, 2) + std::powf(v1.y - v2.y, 2));
		}

		float Distance(const vec2& other) {
			return Utils::vec2::Distance(*this, other);
		}

		float Distance(float x, float y) {
			return std::sqrt(std::powf(this->x - x, 2) + std::powf(this->y - y, 2));
		}
	};
}