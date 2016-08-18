#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>

namespace tfm{
    //@ 3x3 matrix in column vector convention.
    template <typename T>
    class tmat3{
    protected:
        tvec3<T> cols[3];
    public:
        tmat3() { cols[0][0] = 1.0; cols[1][1] = 1.0; cols[2][2] = 1.0; }
        tmat3(T e0, T e1, T e2, T e3, T e4, T e5, T e6, T e7, T e8);
        tmat3(const T m[9]);
        tmat3(const tvec3<T> &v1, const tvec3<T> &v2, const tvec3<T> &v3);

        tvec3<T>&				operator [] (int i);
        const tvec3<T>&			operator [] (int i) const;

        friend tmat3<T>			operator - (const tmat3<T> &m);
        friend tmat3<T>			operator + (const tmat3<T> &m1, const tmat3<T> &m2);
        friend tmat3<T>			operator - (const tmat3<T> &m1, const tmat3<T> &m2);
        friend tmat3<T>			operator * (const tmat3<T> &m1, const tmat3<T> &m2);  // Matrix Multiplication
        friend tvec3<T>			operator * (const tmat3<T> &m, const tvec3<T> &v);   // Vector Multiplication
        friend tmat3<T>			operator * (const tmat3<T> &m, T k);      // Scalar Multiplication
        friend tmat3<T>			operator * (T k, const tmat3<T> &m);      // ...
        friend tmat3<T>			operator / (const tmat3<T> &m, T k);      // ...
        friend tmat3<T>&		operator += (tmat3<T> &m1, const tmat3<T> &m2);
        friend tmat3<T>&		operator -= (tmat3<T> &m1, const tmat3<T> &m2);
        friend std::ostream&	operator << (std::ostream &stream, const tmat3<T> &m);
        friend std::istream&	operator >> (std::istream &stream, tmat3<T> &m);

        //friend std::ostream&       operator<<(std::ostream &stream, const transf &trsf);
        //friend std::istream&       operator>>(std::istream &stream, transf &trsf);
        //      friend const transf   operator*(const transf &trsf1, const transf &trsf2);    // transf.h
    };
    
    template <typename T>
    tmat3<T>			operator - (const tmat3<T> &m);
    template <typename T>
    tmat3<T>			operator + (const tmat3<T> &m1, const tmat3<T> &m2);
    template <typename T>
    tmat3<T>			operator - (const tmat3<T> &m1, const tmat3<T> &m2);
    template <typename T>
    tmat3<T>			operator * (const tmat3<T> &m1, const tmat3<T> &m2);  // Matrix Multiplication
    template <typename T>
    tvec3<T>			operator * (const tmat3<T> &m, const tvec3<T> &v);   // Vector Multiplication
    template <typename T>
    tmat3<T>			operator * (const tmat3<T> &m, T k);      // Scalar Multiplication
    template <typename T>
    tmat3<T>			operator * (T k, const tmat3<T> &m);      // ...
    template <typename T>
    tmat3<T>			operator / (const tmat3<T> &m, T k);      // ...
    template <typename T>
    tmat3<T>&			operator += (tmat3<T> &m1, const tmat3<T> &m2);
    template <typename T>
    tmat3<T>&			operator -= (tmat3<T> &m1, const tmat3<T> &m2);
    template <typename T>
    std::ostream&       operator << (std::ostream &stream, const tmat3<T> &m);
    template <typename T>
    std::istream&       operator >> (std::istream &stream, tmat3<T> &m);

    typedef tmat3<float> mat3;
    typedef tmat3<double> dmat3;
    typedef tmat3<int> imat3;
    typedef tmat3<unsigned int> umat3;
}

#include "mat3.inl"
