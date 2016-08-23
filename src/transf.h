#pragma once

namespace tfm{
    template <typename type_t>
    struct transq;

    template <typename type_t>
    struct transf{
        tmat3<type_t> m;
        tvec3<type_t> v;

        transf() { }
        transf(const tmat3<type_t> &m, const tvec3<type_t> &v) : m(m), v(v) { }

        transf<type_t>  operator * (const transf<type_t> &t)    const;
        tvec3<type_t>   operator * (const tvec3<type_t> &v)     const;

    };

    template <typename type_t>
    std::ostream&   operator << (std::ostream &stream, const transf<type_t> &t);
    template <typename type_t>
    std::istream&	operator >> (std::istream &stream, transf<type_t> &t);

    template <typename type_t>
    transf<type_t>  scale       (type_t x, type_t y, type_t z);
    template <typename type_t>
    transf<type_t>  rotate      (type_t theta, const tvec3<type_t> &direction);
    template <typename type_t>
    transf<type_t>  rotate      (const tvec3<type_t> &v);
    template <typename type_t>
    transf<type_t>  translate   (type_t x, type_t y, type_t z);
    template <typename type_t>
    transf<type_t>  translate   (const tvec3<type_t> &v);
    template <typename type_t>
    transf<type_t>  transf_cast (const transq<type_t> &t);

    template <typename type_t>
    struct transq{
        tquat<type_t> q;
        tvec3<type_t> v;

        transq() { }
        transq(const tquat<type_t> &q, const tvec3<type_t> &v) : q(q), v(v) { }

        transq<type_t>  operator * (const transq<type_t> &t)    const;
        tvec3<type_t>   operator * (const tvec3<type_t> &v)     const;
   };

    template <typename type_t>
    std::ostream&   operator << (std::ostream &stream, const transq<type_t> &t);
    template <typename type_t>
    std::istream&	operator >> (std::istream &stream, transq<type_t> &t);

    template <typename type_t>
    transq<type_t>  q_rotate    (type_t theta, const tvec3<type_t> &direction);
    template <typename type_t>
    transq<type_t>	q_rotate    (const tvec3<type_t> &v);
    template <typename type_t>
    transq<type_t>	q_translate (type_t x, type_t y, type_t z);
    template <typename type_t>
    transq<type_t>	q_translate (const tvec3<type_t> &v);
    template <typename type_t>
    transq<type_t>	transq_cast (const transf<type_t> &t);
}

#include "transf.inl"
