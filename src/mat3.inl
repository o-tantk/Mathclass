#include <cstring>
#include <iomanip>
#include <cassert>

namespace tfm{
    template <typename T>
    tmat3<T>::tmat3<T>(T e0, T e1, T e2, T e3, T e4, T e5, T e6, T e7, T e8) 
    {
        cols[0] = tvec3<T>(e0, e1, e2);
        cols[1] = tvec3<T>(e3, e4, e5);
        cols[2] = tvec3<T>(e6, e7, e8);
    }

    template <typename T>
    tmat3<T>::tmat3<T>(const T m[9]) {
        cols[0] = tvec3<T>(m[0], m[1], m[2]);
        cols[1] = tvec3<T>(m[3], m[4], m[5]);
        cols[2] = tvec3<T>(m[6], m[7], m[8]);
    }

    template <typename T>
    tmat3<T>::tmat3<T>(const tvec3<T> &v1, const tvec3<T> &v2, const tvec3<T> &v3) {
        cols[0] = v1;
        cols[1] = v2;
        cols[2] = v3;
    }

    //@ Quater to matrix.
    template <>
    tmat3<real_t>::tmat3<real_t>(const quat &q) {
        tmat3<real_t> m;

        real_t two_x_square = static_cast<real_t>(2) * q.x * q.x;
        real_t two_y_square = static_cast<real_t>(2) * q.y * q.y;
        real_t two_z_square = static_cast<real_t>(2) * q.z * q.z;
        real_t two_xy = static_cast<real_t>(2) * q.x * q.y;
        real_t two_yz = static_cast<real_t>(2) * q.y * q.z;
        real_t two_zx = static_cast<real_t>(2) * q.z * q.x;
        real_t two_wx = static_cast<real_t>(2) * q.w * q.x;
        real_t two_wy = static_cast<real_t>(2) * q.w * q.y;
        real_t two_wz = static_cast<real_t>(2) * q.w * q.z;

        m[0] = tvec3<real_t>(static_cast<real_t>(1) - two_y_square - two_z_square, two_xy - two_wz, two_zx + two_wy);
        m[1] = tvec3<real_t>(two_xy + two_wz, static_cast<real_t>(1) - two_x_square - two_z_square, two_yz - two_wx);
        m[2] = tvec3<real_t>(two_zx - two_wy, two_yz + two_wx, static_cast<real_t>(1) - two_x_square - two_y_square);

        return m;

        //cols[0] = tvec3<T>(1.0f - 2.0f*(q.y)*(q.y) - 2.0f*(q.z)*(q.z), 2.0f*(q.x)*(q.y) - 2.0f*(q.w)*(q.z), 2.0f*(q.x)*(q.z) + 2.0f*(q.w)*(q.y));
        //cols[1] = tvec3<T>(2.0f*(q.x)*(q.y) + 2.0f*(q.w)*(q.z), 1.0f - 2.0f*(q.x)*(q.x) - 2.0f*(q.z)*(q.z), 2.0f*(q.y)*(q.z) - 2.0f*(q.w)*(q.x));
        //cols[2] = tvec3<T>(2.0f*(q.x)*(q.z) - 2.0f*(q.w)*(q.y), 2.0f*(q.y)*(q.z) + 2.0f*(q.w)*(q.x), 1.0f - 2.0f*(q.x)*(q.x) - 2.0f*(q.y)*(q.y));
    }

    template <typename T>
    tvec3<T>& tmat3<T>::operator [] (int i) {
        assert(0 <= i && i <= 2);
        return cols[i];
    }

    template <typename T>
    const tvec3<T>& tmat3<T>::operator [] (int i) const {
        assert(0 <= i && i <= 2);
        return cols[i];
    }

    template <typename T>
    tmat3<T> operator - (const tmat3<T> &m) {
        return tmat3<T>(-m[0], -m[1], -m[2]);
    }

    template <typename T>
    tmat3<T> operator + (const tmat3<T> &m1, const tmat3<T> &m2) {
        return tmat3<T>(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2]);
    }

    template <typename T>
    tmat3<T> operator - (const tmat3<T> &m1, const tmat3<T> &m2) {
        return tmat3<T>(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2]);
    }

    template <typename T>
    tmat3<T> operator * (const tmat3<T> &m1, const tmat3<T> &m2) {
        tmat3<T> _m;
        memset(&_m[0][0], 0, sizeof(tmat3<T>)); // Need zero matrix not identity matrix.
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                for (int inner = 0; inner < 3; ++inner){
                    _m[i][j] += m1[inner][j] * m2[i][inner];
                }
            }
        }
        return _m;
    }

    template <typename T>
    tvec3<T> operator * (const tmat3<T> &m, const tvec3<T> &v) {
        return tvec3<T>(v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0],
                        v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1],
                        v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2]);
    }

    template <typename T>
    tmat3<T> operator * (const tmat3<T> &m, T k) {
        return tmat3<T>(k * m[0], k * m[1], k * m[2]);
    }

    template <typename T>
    tmat3<T> operator * (T k, const tmat3<T> &m) {
        return tmat3<T>(k * m[0], k * m[1], k * m[2]);
    }

    template <typename T>
    tmat3<T> operator / (const tmat3<T> &m, T k) {
        return tmat3<T>(m[0] / k, m[1] / k, m[2] / k);
    }

    template <typename T>
    tmat3<T>& operator += (tmat3<T> &m1, const tmat3<T> &m2) {
        m1[0] += m2[0];
        m1[1] += m2[1];
        m1[2] += m2[2];
        return m1;
    }

    template <typename T>
    tmat3<T>& operator -= (tmat3<T> &m1, const tmat3<T> &m2) {
        m1[0] -= m2[0];
        m1[1] -= m2[1];
        m1[2] -= m2[2];
        return m1;
    }

    template <typename T>
    std::ostream& operator << (std::ostream &stream, const tmat3<T> &m) {
        stream << std::fixed << std::setprecision(2) << std::setfill('0');
        stream << "(" << m[0] << ", " << m[1] << ", " << m[2] << ")";
        return stream;
    }

    template <typename T>
    std::istream& operator >> (std::istream &stream, tmat3<T> &m) {
        stream >> m[0] >> m[1] >> m[2];
    //	stream >> m[0][0] >> m[0][1] >> m[0][2] >> m[1][0] >> m[1][1] >> m[1][2] >> m[2][0] >> m[2][1] >> m[2][2];
        return stream;
    }
}
