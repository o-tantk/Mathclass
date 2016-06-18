#pragma once

#ifdef DOUBLE_BASED
    typedef double real_t;
    #define PI 3.141592653589793238463
    #define EPSILON 1e-10
    #define radians(x) ((x) * 0.017453292519943295474) // PI / 180'
    #define degrees(x) ((x) * 57.295779513082322864648) // 180' / PI
#else
    typedef float real_t;
    #define PI 3.14159265358979f
    #define EPSILON 1e-10f
    #define radians(x) ((x) * 0.01745329238474f) // PI / 180'
    #define degrees(x) ((x) * 57.29577636718750f) // 180' / PI
#endif

#define clamp(x, a, b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

#include "vec3.h"
#include "mat3.h"
#include "quat.h"
//#include "Transform.h"
//#include <iostream>
