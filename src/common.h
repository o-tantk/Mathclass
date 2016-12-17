#pragma once

#include <cmath>

namespace tfm {
    template <typename type_t>
    constexpr type_t epsilon() {
        return type_t(1e-10);
    }

    template <typename type_t>
    constexpr type_t pi() {
        return type_t(acos(-1.0));
//        return type_t(3.141592653589793238463);
    }

    //@ PI / 180`
    template <typename type_t>
    constexpr type_t pi_per_half() {
        return type_t(pi<double>() / 180.0);
//        return type_t(0.017453292519943295474);
    }

    //@ 180` / PI
    template <typename type_t>
    constexpr type_t half_per_pi() {
        return type_t(180.0 / pi<double>());
//        return type_t(57.295779513082322864648);
    }

    template <typename type_t>
    type_t radians(type_t degrees) {
        return degrees * pi_per_half<type_t>();
    }

    template <typename type_t>
    type_t degrees(type_t radians) {
        return radians * half_per_pi<type_t>();
    }

    template <typename type_t>
    type_t clamp(type_t x, type_t a, type_t b) {
        return x < a ? a : (x > b ? b : x);
    }
}
