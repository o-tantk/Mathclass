namespace tfm{
    // transf //////////////////////////////////////////////////////////

    template <typename type_t>
    transf<type_t> transf<type_t>::operator * (const transf<type_t> &t) const {
        return transf<type_t>(this->m * t.m, this->m * t.v + this->v);
    }

    template <typename type_t>
    tvec3<type_t> transf<type_t>::operator * (const tvec3<type_t> &v) const {
        return this->m * v + this->v;
    }

    template <typename type_t>
    std::ostream& operator << (std::ostream &stream, const transf<type_t> &t) {
        stream << t.m << " " << t.v;
        return stream;
    }

    template <typename type_t>
    std::istream& operator >> (std::istream &stream, transf<type_t> &t) {
        stream >> t.m >> t.v;
        return stream;
    }

    template <typename type_t>
    transf<type_t> scale(type_t x, type_t y, type_t z) {
        return transf<type_t>(tmat3<type_t>(x, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, z), tvec3<type_t>());
    }

    template <typename type_t>
    transf<type_t> scale(const tvec3<type_t> &v) {
        return transf<type_t>(tmat3<type_t>(v.x, 0.0, 0.0, 0.0, v.y, 0.0, 0.0, 0.0, v.z), tvec3<type_t>());
    }

    // Axis-angle rotation. u must be unit vector.
    template <typename type_t>
    tmat3<type_t> axis_angle_rotation(type_t theta, const tvec3<type_t> &u) {
        tmat3<type_t> vvt(u.x * u.x, u.x * u.y, u.x * u.z,
                        u.y * u.x, u.y * u.y, u.y * u.z,
                        u.z * u.x, u.z * u.y, u.z * u.z);
        // v cross for column vector convention
        // (  0 -z  y )
        // (  z  0 -x )
        // ( -y  x  0 )
        tmat3<type_t> vx(0.0, u.z, -u.y, -u.z, 0.0, u.x, u.y, -u.x, 0.0);
        return vvt + static_cast<type_t>(cos(theta)) * (tmat3<type_t>() - vvt) + static_cast<type_t>(sin(theta)) * vx;
    }

    template <typename type_t>
    transf<type_t> rotate(type_t x, type_t y, type_t z) {
        return rotate(tvec3<type_t>(x, y, z));
    }

    template <typename type_t>
    transf<type_t> rotate(type_t theta, const tvec3<type_t> &direction) {
        type_t l = length(direction);
        if (theta == 0.0 || l == 0.0){
            return transf<type_t>();
        }
        else {
            return transf<type_t>(axis_angle_rotation(theta, direction / l), tvec3<type_t>());
        }
    }

    template <typename type_t>
    transf<type_t> rotate(const tvec3<type_t> &v) {
        type_t theta = length(v);
        if (theta == 0.0){
            return transf<type_t>();
        }
        else {
            return transf<type_t>(axis_angle_rotation(theta, v / theta), tvec3<type_t>());
        }
    }

    template <typename type_t>
    transf<type_t> translate(type_t x, type_t y, type_t z) {
        return transf<type_t>(tmat3<type_t>(), tvec3<type_t>(x, y, z));
    }

    template <typename type_t>
    transf<type_t> translate(const tvec3<type_t> &v) {
        return transf<type_t>(tmat3<type_t>(), v);
    }

    template <typename type_t>
    transf<type_t> transf_cast(const transq<type_t> &t) {
        return transf<type_t>(mat3_cast(t.q), t.v);
    }

    // transq<type_t> //////////////////////////////////////////////////////////

    template <typename type_t>
    transq<type_t> transq<type_t>::operator * (const transq<type_t> &t) const {
        return transq<type_t>(this->q * t.q, (this->q * tquat<type_t>(0, t.v) * inverse(this->q)).v + this->v);
    }

    template <typename type_t>
    tvec3<type_t> transq<type_t>::operator * (const tvec3<type_t> &v) const {
        return (this->q * tquat<type_t>(0, v) * inverse(this->q)).v + this->v;
    }

    template <typename type_t>
    std::ostream& operator << (std::ostream &stream, const transq<type_t> &t) {
        stream << t.q << " " << t.v;
        return stream;
    }

    template <typename type_t>
    std::istream& operator >> (std::istream &stream, transq<type_t> &t) {
        stream >> t.q >> t.v;
        return stream;
    }

    template <typename type_t>
    transq<type_t> q_rotate (type_t x, type_t y, type_t z) {
        return q_rotate(tvec3<type_t>(x, y, z));
    }

    template <typename type_t>
    transq<type_t> q_rotate(type_t theta, const tvec3<type_t> &direction) {
        type_t l = length(direction);
        if (theta == 0.0 || l == 0.0){
            return transq<type_t>();
        }
        return transq<type_t>(exp(static_cast<type_t>(0.5) * theta * (direction / l)), tvec3<type_t>());
    }

    template <typename type_t>
    transq<type_t> q_rotate(const tvec3<type_t> &v) {
        if (length(v) == 0.0){
            return transq<type_t>();
        }
        return transq<type_t>(exp(static_cast<type_t>(0.5) * v), tvec3<type_t>());
    }

    template <typename type_t>
    transq<type_t> q_translate(type_t x, type_t y, type_t z) {
        return transq<type_t>(tquat<type_t>(), tvec3<type_t>(x, y, z));
    }

    template <typename type_t>
    transq<type_t> q_translate(const tvec3<type_t> &v) {
        return transq<type_t>(tquat<type_t>(), v);
    }

    template <typename type_t>
    transq<type_t> transq_cast(const transf<type_t> &t) {
        return transq<type_t>(normalize(quat_cast(t.m)), t.v);
    }
}
