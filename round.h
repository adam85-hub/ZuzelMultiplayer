#pragma once
#include <cmath>

namespace Utils {
    static float roundToNearestInt(float fValue)
    {
        return fValue < 0 ? std::ceil(fValue - 0.5) : std::floor(fValue + 0.5);
    }
    
    static double roundToNearestInt(double dValue)
    {
        return dValue < 0 ? std::ceil(dValue - 0.5) : std::floor(dValue + 0.5);
    }
}
