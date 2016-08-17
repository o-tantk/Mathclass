#pragma once

namespace tfm{
    struct quat{
        union {
            struct { real_t s; vec3 v; };
            struct { real_t w, x, y, z; };
        };

        quat() : w(1.0) { }
        quat(real_t w, real_t x, real_t y, real_t z) : w(w), x(x), y(y), z(z) { }
        quat(real_t s, const tvec3<real_t> &v) : s(s), v(v) { }
        quat(const tmat3<real_t> &m);
    };

    quat operator - (const quat &q);
    quat operator + (const quat &q1, const quat &q2);
    quat operator - (const quat &q1, const quat &q2);
    quat operator * (const quat &q1, const quat &q2);
    quat operator * (const quat &q, real_t k);
    quat operator * (real_t k, const quat &q);
    quat operator / (const quat &q, real_t k);
    std::ostream& operator << (std::ostream &stream, const quat &q);
    std::istream& operator >> (std::istream &stream, quat &q);

    real_t   length(const quat &q);
    quat     inverse(const quat &q);
    quat     normalize(const quat &q);
    real_t   dot(const quat &q1, const quat &q2);
    quat     exp(const vec3 &v);
    vec3     log(const quat &q);
    quat     slerp(const quat &q1, const quat &q2, real_t t);
}

#include "quat.inl"
