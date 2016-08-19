#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <cstring>

namespace tfm{
    template <typename type_t>
    struct tvec3{
        union {
            struct { type_t x, y, z; };
            struct { type_t r, g, b; };
        };

        tvec3() : x(0), y(0), z(0) { }
        tvec3(type_t x, type_t y, type_t z) : x(x), y(y), z(z) { }

        type_t&			operator [] (int i);
        type_t			operator [] (int i) const;

        tvec3<type_t>	operator - ()                           const;
        tvec3<type_t>	operator + (const tvec3<type_t> &v)     const;
        tvec3<type_t>	operator - (const tvec3<type_t> &v)     const;
        tvec3<type_t>	operator * (const tvec3<type_t> &v)     const; //@ Pointwise multiplication.
        tvec3<type_t>	operator * (type_t k)                   const;
        tvec3<type_t>	operator / (type_t k)                   const;
        tvec3<type_t>&	operator += (const tvec3<type_t> &v);
        tvec3<type_t>&	operator -= (const tvec3<type_t> &v);
        tvec3<type_t>&	operator *= (const tvec3<type_t> &v);
        tvec3<type_t>&	operator += (type_t k);
        tvec3<type_t>&	operator -= (type_t k);
        tvec3<type_t>&	operator *= (type_t k);
        tvec3<type_t>&	operator /= (type_t k);
    };

    template <typename type_t>
    tvec3<type_t>		operator * (type_t k, const tvec3<type_t> &v);
    template <typename type_t>
    std::ostream&       operator << (std::ostream &stream, const tvec3<type_t> &v);
    template <typename type_t>
    std::istream&       operator >> (std::istream &stream, tvec3<type_t> &v);

    template <typename type_t>
    type_t   			isqrt       (const tvec3<type_t> &v); //@ Fast inverse square root from Quake3
    template <typename type_t>
    type_t   			length      (const tvec3<type_t> &v);
    template <typename type_t>
    type_t              sqrLength   (const tvec3<type_t> &v);
    template <typename type_t>
    tvec3<type_t>		normalize   (const tvec3<type_t> &v);
    template <typename type_t>
    type_t	    		dot         (const tvec3<type_t> &v1, const tvec3<type_t> &v2); //@ Dot product
    template <typename type_t>
    tvec3<type_t>		cross       (const tvec3<type_t> &v1, const tvec3<type_t> &v2); //@ Cross product

    typedef tvec3<float>        vec3;
    typedef tvec3<double>       dvec3;
    typedef tvec3<int>          ivec3;
    typedef tvec3<unsigned int> uvec3;
}

#include "vec3.inl"
