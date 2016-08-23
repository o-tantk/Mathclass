#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>

namespace tfm{
    //@ 3x3 matrix in column vector convention.
    template <typename type_t>
    class tmat3{
    protected:
        tvec3<type_t> cols[3];
    public:
        tmat3() { cols[0][0] = 1.0; cols[1][1] = 1.0; cols[2][2] = 1.0; }
        tmat3(type_t e0, type_t e1, type_t e2, type_t e3, type_t e4, type_t e5, type_t e6, type_t e7, type_t e8);
        tmat3(const type_t m[9]);
        tmat3(const tvec3<type_t> &v1, const tvec3<type_t> &v2, const tvec3<type_t> &v3);

        tvec3<type_t>&          operator [] (int i);
        const tvec3<type_t>&    operator [] (int i) const;

        tmat3<type_t>			operator - ()                           const;
        tmat3<type_t>			operator + (const tmat3<type_t> &m)     const;
        tmat3<type_t>			operator - (const tmat3<type_t> &m)     const;
        tmat3<type_t>			operator * (const tmat3<type_t> &m)     const; // Matrix Multiplication
        tvec3<type_t>			operator * (const tvec3<type_t> &v)     const; // Vector Multiplication
        tmat3<type_t>			operator * (type_t k)                   const; // Scalar Multiplication
        tmat3<type_t>			operator / (type_t k)                   const; // Scalar Division
        tmat3<type_t>&		    operator += (const tmat3<type_t> &m);
        tmat3<type_t>&		    operator -= (const tmat3<type_t> &m);
        tmat3<type_t>&          operator *= (const tmat3<type_t> &m);
    };

    template <typename type_t>
    tmat3<type_t>		operator * (type_t k, const tmat3<type_t> &m); // Scalar Multiplication
    template <typename type_t>
    std::ostream&       operator << (std::ostream &stream, const tmat3<type_t> &m);
    template <typename type_t>
    std::istream&       operator >> (std::istream &stream, tmat3<type_t> &m);

    typedef tmat3<float> mat3;
    typedef tmat3<double> dmat3;
    typedef tmat3<int> imat3;
    typedef tmat3<unsigned int> umat3;
}

#include "mat3.inl"
