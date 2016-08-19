namespace tfm{
    template <typename type_t>
    tmat3<type_t>::tmat3(type_t e0, type_t e1, type_t e2, type_t e3, type_t e4, type_t e5, type_t e6, type_t e7, type_t e8) 
    {
        cols[0] = tvec3<type_t>(e0, e1, e2);
        cols[1] = tvec3<type_t>(e3, e4, e5);
        cols[2] = tvec3<type_t>(e6, e7, e8);
    }

    template <typename type_t>
    tmat3<type_t>::tmat3(const type_t m[9]) {
        cols[0] = tvec3<type_t>(m[0], m[1], m[2]);
        cols[1] = tvec3<type_t>(m[3], m[4], m[5]);
        cols[2] = tvec3<type_t>(m[6], m[7], m[8]);
    }

    template <typename type_t>
    tmat3<type_t>::tmat3(const tvec3<type_t> &v1, const tvec3<type_t> &v2, const tvec3<type_t> &v3) {
        cols[0] = v1;
        cols[1] = v2;
        cols[2] = v3;
    }
/*
    //@ Quater to matrix.
    template <typename type_t>
    tmat3<type_t> mat3_cast(const quat &q) {
        tmat3<type_t> m;

        type_t two_x_square = static_cast<type_t>(2) * q.x * q.x;
        type_t two_y_square = static_cast<type_t>(2) * q.y * q.y;
        type_t two_z_square = static_cast<type_t>(2) * q.z * q.z;
        type_t two_xy = static_cast<type_t>(2) * q.x * q.y;
        type_t two_yz = static_cast<type_t>(2) * q.y * q.z;
        type_t two_zx = static_cast<type_t>(2) * q.z * q.x;
        type_t two_wx = static_cast<type_t>(2) * q.w * q.x;
        type_t two_wy = static_cast<type_t>(2) * q.w * q.y;
        type_t two_wz = static_cast<type_t>(2) * q.w * q.z;

        m[0] = tvec3<type_t>(static_cast<type_t>(1) - two_y_square - two_z_square, two_xy - two_wz, two_zx + two_wy);
        m[1] = tvec3<type_t>(two_xy + two_wz, static_cast<type_t>(1) - two_x_square - two_z_square, two_yz - two_wx);
        m[2] = tvec3<type_t>(two_zx - two_wy, two_yz + two_wx, static_cast<type_t>(1) - two_x_square - two_y_square);

        return m;
    }
*/
    // m[i]
    template <typename type_t>
    tvec3<type_t>& tmat3<type_t>::operator [] (int i) {
        assert(0 <= i && i <= 2);
        return cols[i];
    }

    // m[i] readonly
    template <typename type_t>
    const tvec3<type_t>& tmat3<type_t>::operator [] (int i) const {
        assert(0 <= i && i <= 2);
        return cols[i];
    }

    // -m
    template <typename type_t>
    tmat3<type_t> tmat3<type_t>::operator - () const {
        return tmat3<type_t>(-(*this)[0], -(*this)[1], -(*this)[2]);
    }

    // m1 + m2
    template <typename type_t>
    tmat3<type_t> tmat3<type_t>::operator + (const tmat3<type_t> &m) const {
        return tmat3<type_t>((*this)[0] + m[0], (*this)[1] + m[1], (*this)[2] + m[2]);
    }

    // m1 - m2
    template <typename type_t>
    tmat3<type_t> tmat3<type_t>::operator - (const tmat3<type_t> &m) const{
        return tmat3<type_t>((*this)[0] - m[0], (*this)[1] - m[1], (*this)[2] - m[2]);
    }

    // m1 * m2
    template <typename type_t>
    tmat3<type_t> tmat3<type_t>::operator * (const tmat3<type_t> &m) const {
        tmat3<type_t> _m;
        memset(&_m[0][0], 0, sizeof(tmat3<type_t>)); // Need zero matrix not identity matrix.
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                for (int inner = 0; inner < 3; ++inner){
                    _m[i][j] += (*this)[inner][j] * m[i][inner];
                }
            }
        }
        return _m;
    }

    // m * v
    template <typename type_t>
    tvec3<type_t> tmat3<type_t>::operator * (const tvec3<type_t> &v) const {
        return tvec3<type_t>(v.x * (*this)[0][0] + v.y * (*this)[1][0] + v.z * (*this)[2][0],
                        v.x * (*this)[0][1] + v.y * (*this)[1][1] + v.z * (*this)[2][1],
                        v.x * (*this)[0][2] + v.y * (*this)[1][2] + v.z * (*this)[2][2]);
    }

    // m * k
    template <typename type_t>
    tmat3<type_t> tmat3<type_t>::operator * (type_t k) const {
        return tmat3<type_t>(k * (*this)[0], k * (*this)[1], k * (*this)[2]);
    }

    // m / k
    template <typename type_t>
    tmat3<type_t> tmat3<type_t>::operator / (type_t k) const {
        return tmat3<type_t>((*this)[0] / k, (*this)[1] / k, (*this)[2] / k);
    }

    // m1 += m2
    template <typename type_t>
    tmat3<type_t>& tmat3<type_t>::operator += (const tmat3<type_t> &m) {
        (*this)[0] += m[0];
        (*this)[1] += m[1];
        (*this)[2] += m[2];
        return *this;
    }

    // m1 -= m2
    template <typename type_t>
    tmat3<type_t>& tmat3<type_t>::operator -= (const tmat3<type_t> &m) {
        (*this)[0] -= m[0];
        (*this)[1] -= m[1];
        (*this)[2] -= m[2];
        return *this;
    }

    // m1 *= m2
    template <typename type_t>
    tmat3<type_t>& tmat3<type_t>::operator *= (const tmat3<type_t> &m) {
        tmat3<type_t> _m = (*this) * m;
        *this = _m;
        return *this;
    }

    // k * m
    template <typename type_t>
    tmat3<type_t> operator * (type_t k, const tmat3<type_t> &m) {
        return tmat3<type_t>(k * m[0], k * m[1], k * m[2]);
    }

    template <typename type_t>
    std::ostream& operator << (std::ostream &stream, const tmat3<type_t> &m) {
        stream << std::fixed << std::setprecision(2) << std::setfill('0');
        stream << "(" << m[0] << ", " << m[1] << ", " << m[2] << ")";
        return stream;
    }

    template <typename type_t>
    std::istream& operator >> (std::istream &stream, tmat3<type_t> &m) {
        stream >> m[0] >> m[1] >> m[2];
        return stream;
    }
}
