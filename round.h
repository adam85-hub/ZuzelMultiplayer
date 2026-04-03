#pragma once
#include <cmath>

namespace Utils {
    float roundToNearestInt(float fValue)
    {
        return fValue < 0 ? std::ceil(fValue - 0.5) : std::floor(fValue + 0.5);
    }
}
