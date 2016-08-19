namespace tfm{
//    tquat<type_t>::quat(const mat3 &m) {
//        tquat<type_t> q;
//        real_t trace, s;
//
//        trace = m[0][0] + m[1][1] + m[2][2];
//        if (trace > 0.0){
//            s = static_cast<real_t>(sqrt(1.0 + trace));
//            q.w = s * static_cast<real_t>(0.5);
//            s = static_cast<real_t>(0.5) / s;
//            q.x = (m[2][1] - m[1][2]) * s;
//            q.y = (m[0][2] - m[2][0]) * s;
//            q.z = (m[1][0] - m[0][1]) * s;
//        }
//        else if ((m[0][0] > m[1][1]) && (m[0][0] > m[2][2])){
//            s = static_cast<real_t>(2.0 * sqrt(1.0 + m[0][0] - m[1][1] - m[2][2]));
//            q.w = (m[2][1] - m[1][2]) / s;
//            q.x = static_cast<real_t>(0.25) * s;
//            q.y = (m[0][1] + m[1][0]) / s;
//            q.z = (m[0][2] + m[2][0]) / s;
//        }
//        else if (m[1][1] > m[2][2]){
//            s = static_cast<real_t>(2.0 * sqrt(1.0 + m[1][1] - m[0][0] - m[2][2]));
//            q.w = (m[0][2] - m[2][0]) / s;
//            q.x = (m[0][1] + m[1][0]) / s;
//            q.y = static_cast<real_t>(0.25) * s;
//            q.z = (m[1][2] + m[2][1]) / s;
//        }
//        else{
//            s = static_cast<real_t>(2.0 * sqrt(1.0 + m[2][2] - m[0][0] - m[1][1]));
//            q.w = (m[1][0] - m[0][1]) / s;
//            q.x = (m[0][2] + m[2][0]) / s;
//            q.y = (m[1][2] + m[2][1]) / s;
//            q.z = static_cast<real_t>(0.25) * s;
//        }
//
//        return q;
//    }

    template <typename type_t>
    tquat<type_t> tquat<type_t>::operator - () const {
        return tquat<type_t>(-(this->w), -(this->v));
    }

    template <typename type_t>
    tquat<type_t> tquat<type_t>::operator + (const tquat<type_t> &q) const {
        return tquat<type_t>(this->w + q.w, this->v + q.v);
    }

    template <typename type_t>
    tquat<type_t> tquat<type_t>::operator - (const tquat<type_t> &q) const {
        return tquat<type_t>(this->w - q.w, this->v - q.v);
    }

    template <typename type_t>
    tquat<type_t> tquat<type_t>::operator * (const tquat<type_t> &q) const {
        return tquat<type_t>(this->w * q.w - dot(this->v, q.v), this->w * q.v + q.w * this->v + cross(this->v, q.v));
    }

    template <typename type_t>
    tquat<type_t> tquat<type_t>::operator * (real_t k) const {
        return tquat<type_t>(this->w * k, this->v * k);
    }

    // q * k
    template <typename type_t>
    tquat<type_t> tquat<type_t>::operator / (real_t k) const {
        return tquat<type_t>(this->w / k, this->v / k);
    }

    // k * q
    template <typename type_t>
    tquat<type_t> operator * (real_t k, const tquat<type_t> &q) {
        return tquat<type_t>(q.w * k, q.v * k);
    }

    template <typename type_t>
    std::ostream& operator << (std::ostream &stream, const tquat<type_t> &q) {
        stream << std::fixed << std::setprecision(2) << std::setfill('0');
        stream << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
        return stream;
    }

    template <typename type_t>
    std::istream& operator >> (std::istream &stream, tquat<type_t> &q) {
        stream >> q.w >> q.x >> q.y >> q.z;
        return stream;
    }

    template <typename type_t>
    type_t length(const tquat<type_t> &q) {
        return type_t(sqrt(dot(q, q)));
    }

    template <typename type_t>
    tquat<type_t> inverse(const tquat<type_t> &q) {
        return tquat<type_t>(q.w, -q.v);
    }

    template <typename type_t>
    tquat<type_t> normalize(const tquat<type_t> &q) {
        return tquat<type_t>(q / length(q));
    }

    template <typename type_t>
    type_t dot(const tquat<type_t> &q1, const tquat<type_t> &q2) {
        return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
    }

    template <typename type_t>
    tquat<type_t> exp(const tvec3<type_t> &v) {
        type_t theta = length(v);
        if (theta < epsilon<type_t>()){
            return tquat<type_t>();
        }
        return tquat<type_t>(type_t(cos(theta)), type_t(sin(theta)) * (v / theta));
    }

    template <typename type_t>
    tvec3<type_t> log(const tquat<type_t> &q) {
        type_t v_length = length(q.v);
        if (v_length < epsilon<type_t>()){
            if (q.w > 0.0){
                return tvec3<type_t>();
            }
            else if (q.w < 0.0){
                return tvec3<type_t>(pi<type_t>(), 0.0, 0.0);
            }
            else{
                return tvec3<type_t>(std::numeric_limits<type_t>::infinity(),
                                    std::numeric_limits<type_t>::infinity(),
                                    std::numeric_limits<type_t>::infinity());
            }
        }
        else{
            type_t theta = type_t(atan2(v_length, q.w));
            return theta * (q.v / v_length);
        }
    }

    template <typename type_t>
    tquat<type_t> slerp(const quat &q1, const quat &q2, type_t t) {
        // This is a general form, but commonly not used in practice.
        //return q1 * exp(t * log(inverse(this-> * q2));

        tquat<type_t> _q2 = q2;

        type_t cos_theta = dot(q1, q2);
        // If cos < 0, the interpolation will take the long way.
        // To fix this, one of the orientations must be negated.
        if (cos_theta < 0.0){
            _q2 = -q2;
            cos_theta = -cos_theta;
        }

        // If theta = 0, sin becoming a zero.
        // In this situation, lerp can be used.
        if (1.0 - cos_theta < epsilon<type_t>()){
            return (1 - t) * q1 + t * _q2;
        }
        else{
            type_t theta = type_t(acos(cos_theta));
            return (type_t(sin((static_cast<real_t>(1.0) - t) * theta)) * q1 + type_t(sin(t * theta)) * _q2) / type_t(sin(theta));
        }
    }
}
