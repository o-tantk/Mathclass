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

    template <typename type_t>
    type_t determinant (const tmat3<type_t> &m) {
        return + m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
                - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
                + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
    }

    template <typename type_t>
    tmat3<type_t> transpose (const tmat3<type_t> &m) {
        return tmat3<type_t>(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1], m[0][2], m[1][2], m[2][2]);
    }

    template <typename type_t>
    tmat3<type_t> inverse (const tmat3<type_t> &m) {
        type_t D = determinant(m);
        assert(D != static_cast<type_t>(0));
        type_t oneOverDeterminant = static_cast<type_t>(1) / D;

        return tmat3<type_t>(
            + (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * oneOverDeterminant,
            - (m[0][1] * m[2][2] - m[2][1] * m[0][2]) * oneOverDeterminant,
            + (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * oneOverDeterminant,
            - (m[1][0] * m[2][2] - m[2][0] * m[1][2]) * oneOverDeterminant,
            + (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * oneOverDeterminant,
            - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) * oneOverDeterminant,
            + (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * oneOverDeterminant,
            - (m[0][0] * m[2][1] - m[2][0] * m[0][1]) * oneOverDeterminant,
            + (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * oneOverDeterminant
        );
    }
}
