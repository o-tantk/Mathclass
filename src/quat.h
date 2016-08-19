#pragma once

#include <iomanip>
#include <limits>
#include <cmath>
#include <cassert>

namespace tfm{
    template <typename type_t>
    struct tquat{
        union {
            struct { type_t s; tvec3<type_t> v; };
            struct { type_t w, x, y, z; };
        };

        tquat() : w(1.0) { }
        tquat(type_t w, type_t x, type_t y, type_t z) : w(w), x(x), y(y), z(z) { }
        tquat(type_t s, const tvec3<type_t> &v) : s(s), v(v) { }
        //tquat(const tmat3<type_t> &m);

        tquat<type_t> operator - ()                         const;
        tquat<type_t> operator + (const tquat<type_t> &q)   const;
        tquat<type_t> operator - (const tquat<type_t> &q)   const;
        tquat<type_t> operator * (const tquat<type_t> &q)   const;
        tquat<type_t> operator * (type_t k)                 const;
        tquat<type_t> operator / (type_t k)                 const;
    };

    template <typename type_t>
    tquat<type_t> operator * (type_t k, const quat<type_t> &q);
    template <typename type_t>
    std::ostream& operator << (std::ostream &stream, const tquat<type_t> &q);
    template <typename type_t>
    std::istream& operator >> (std::istream &stream, tquat<type_t> &q);

    template <typename type_t>
    type_t              length      (const tquat<type_t> &q);
    template <typename type_t>
    tquat<type_t>       inverse     (const quat &q);
    template <typename type_t>
    tquat<type_t>       normalize   (const quat &q);
    template <typename type_t>
    type_t              dot         (const tquat<type_t> &q1, const tquat<type_t> &q2);
    template <typename type_t>
    tquat<type_t>       exp         (const tvec3<type_t> &v);
    template <typename type_t>
    tvec3<type_t>       log         (const tquat<type_t> &q);
    template <typename type_t>
    tquat<type_t>       slerp       (const tquat<type_t> &q1, const tquat<type_t> &q2, type_t t);

    typedef tquat<float>    quat;
    typedef tquat<double>   dquat;
}

#include "quat.inl"
