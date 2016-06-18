#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <cstring>

namespace tfm{
    template <typename T>
    struct tvec3{
        union {
            struct { T x, y, z; };
            struct { T r, g, b; };
        };

        tvec3() : x(0), y(0), z(0) { }
        tvec3(T x, T y, T z) : x(x), y(y), z(z) { }

        T&			operator [] (int i);
        T			operator [] (int i) const;
    };

    template <typename T>
    tvec3<T>		operator - (const tvec3<T> &v);
    template <typename T>
    tvec3<T>		operator + (const tvec3<T> &v1, const tvec3<T> &v2);
    template <typename T>
    tvec3<T>		operator - (const tvec3<T> &v1, const tvec3<T> &v2);
    template <typename T>
    tvec3<T>		operator * (const tvec3<T> &v1, const tvec3<T> &v2);	//@ Pointwise multiplication.
    template <typename T>
    tvec3<T>		operator * (const tvec3<T> &v, real_t k);
    template <typename T>
    tvec3<T>		operator * (real_t k, const tvec3<T> &v);
    template <typename T>
    tvec3<T>		operator / (const tvec3<T> &v, real_t k);
    template <typename T>
    tvec3<T>&		operator += (tvec3<T> &v1, const tvec3<T> &v2);
    template <typename T>
    tvec3<T>&		operator -= (tvec3<T> &v1, const tvec3<T> &v2);
    template <typename T>
    tvec3<T>&		operator *= (tvec3<T> &v1, const tvec3<T> &v2);
    template <typename T>
    tvec3<T>&		operator += (tvec3<T> &v, real_t k);
    template <typename T>
    tvec3<T>&		operator -= (tvec3<T> &v, real_t k);
    template <typename T>
    tvec3<T>&		operator *= (tvec3<T> &v, real_t k);
    template <typename T>
    tvec3<T>&		operator /= (tvec3<T> &v, real_t k);
    template <typename T>
    std::ostream&	operator << (std::ostream &stream, const tvec3<T> &v);
    template <typename T>
    std::istream&	operator >> (std::istream &stream, tvec3<T> &v);

    template <typename T>
    real_t			isqrt(const tvec3<T> &v);
    template <typename T>
    real_t			length(const tvec3<T> &v);
    template <typename T>
    tvec3<T>		normalize(const tvec3<T> &v);
    template <typename T>
    real_t			dot(const tvec3<T> &v1, const tvec3<T> &v2);
    template <typename T>
    tvec3<T>		cross(const tvec3<T> &v1, const tvec3<T> &v2);

    typedef tvec3<real_t> vec3;
    typedef tvec3<int> ivec3;
    typedef tvec3<unsigned int> uvec3;
}

#include "vec3.inl"
