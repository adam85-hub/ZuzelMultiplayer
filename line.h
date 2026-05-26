#pragma once
#include <cmath>
#include <algorithm>
#include "vec2.h"

namespace Utils {
    struct line {
        Utils::vec2 a, b;

        //Zwraca strukturê line, gdzie 'a' to punkt na bie¿¹cej linii, a 'b' na linii 'other'.
        line get_closest_points(const line& other) const {
            Utils::vec2 u = b - a;
            Utils::vec2 v = other.b - other.a;
            Utils::vec2 w = a - other.a;

            float a_dot = u.dot(u);
            float b_dot = u.dot(v);
            float c_dot = v.dot(v);
            float d_dot = u.dot(w);
            float e_dot = v.dot(w);

            float D = a_dot * c_dot - b_dot * b_dot;
            float sc, sN, sD = D;
            float tc, tN, tD = D;

            // Obs³uga linii równoleg³ych
            if (D < 0.0001f) {
                sN = 0.0f;
                sD = 1.0f;
                tN = e_dot;
                tD = c_dot;
            }
            else {
                sN = (b_dot * e_dot - c_dot * d_dot);
                tN = (a_dot * e_dot - b_dot * d_dot);

                if (sN < 0.0f) {
                    sN = 0.0f;
                    tN = e_dot;
                    tD = c_dot;
                }
                else if (sN > sD) {
                    sN = sD;
                    tN = e_dot + b_dot;
                    tD = c_dot;
                }
            }

            // Ograniczenie parametru t do zakresu [0, 1]
            if (tN < 0.0f) {
                tN = 0.0f;
                if (-d_dot < 0.0f) sN = 0.0f;
                else if (-d_dot > a_dot) sN = sD;
                else { sN = -d_dot; sD = a_dot; }
            }
            else if (tN > tD) {
                tN = tD;
                if ((-d_dot + b_dot) < 0.0f) sN = 0.0f;
                else if ((-d_dot + b_dot) > a_dot) sN = sD;
                else { sN = (-d_dot + b_dot); sD = a_dot; }
            }

            sc = (std::abs(sN) < 0.0001f ? 0.0f : sN / sD);
            tc = (std::abs(tN) < 0.0001f ? 0.0f : tN / tD);

            return {
                a + (u * sc),         // Punkt na l1
                other.a + (v * tc)    // Punkt na l2
            };
        }

        float get_distance(const line& other) const {
            line closest = get_closest_points(other);
            Utils::vec2 diff = closest.b - closest.a;
            return std::sqrt(diff.dot(diff));
        }
    };
}
