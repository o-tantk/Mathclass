#include <iomanip>
#include <limits>

namespace tfm{
    quat::quat(const mat3 &m) {
        quat q;
        real_t trace, s;

        trace = m[0][0] + m[1][1] + m[2][2];
        if (trace > 0.0){
            s = static_cast<real_t>(sqrt(1.0 + trace));
            q.w = s * static_cast<real_t>(0.5);
            s = static_cast<real_t>(0.5) / s;
            q.x = (m[2][1] - m[1][2]) * s;
            q.y = (m[0][2] - m[2][0]) * s;
            q.z = (m[1][0] - m[0][1]) * s;
        }
        else if ((m[0][0] > m[1][1]) && (m[0][0] > m[2][2])){
            s = static_cast<real_t>(2.0 * sqrt(1.0 + m[0][0] - m[1][1] - m[2][2]));
            q.w = (m[2][1] - m[1][2]) / s;
            q.x = static_cast<real_t>(0.25) * s;
            q.y = (m[0][1] + m[1][0]) / s;
            q.z = (m[0][2] + m[2][0]) / s;
        }
        else if (m[1][1] > m[2][2]){
            s = static_cast<real_t>(2.0 * sqrt(1.0 + m[1][1] - m[0][0] - m[2][2]));
            q.w = (m[0][2] - m[2][0]) / s;
            q.x = (m[0][1] + m[1][0]) / s;
            q.y = static_cast<real_t>(0.25) * s;
            q.z = (m[1][2] + m[2][1]) / s;
        }
        else{
            s = static_cast<real_t>(2.0 * sqrt(1.0 + m[2][2] - m[0][0] - m[1][1]));
            q.w = (m[1][0] - m[0][1]) / s;
            q.x = (m[0][2] + m[2][0]) / s;
            q.y = (m[1][2] + m[2][1]) / s;
            q.z = static_cast<real_t>(0.25) * s;
        }

        return q;
    }

    quat operator - (const quat &q) {
        return quat(-q.w, -q.v);
    }

    quat operator + (const quat &q1, const quat &q2) {
        return quat(q1.w + q2.w, q1.v + q2.v);
    }

    quat operator - (const quat &q1, const quat &q2) {
        return quat(q1.w - q2.w, q1.v - q2.v);
    }

    quat operator * (const quat &q1, const quat &q2) {
        return quat(q1.w * q2.w - dot(q1.v, q2.v), q1.w * q2.v + q2.w * q1.v + cross(q1.v, q2.v));
    }

    quat operator * (const quat &q, real_t k) {
        return quat(q.w * k, q.v * k);
    }

    quat operator * (real_t k, const quat &q) {
        return quat(q.w * k, q.v * k);
    }

    quat operator / (const quat &q, real_t k) {
        return quat(q.w / k, q.v / k);
    }

    std::ostream& operator << (std::ostream &stream, const quat &q) {
        stream << std::fixed << std::setprecision(2) << std::setfill('0');
        stream << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
        return stream;
    }
    std::istream& operator >> (std::istream &stream, quat &q) {
        stream >> q.w >> q.x >> q.y >> q.z;
        return stream;
    }

    real_t length(const quat &q) {
        return sqrt(dot(q, q));
    }

    quat inverse(const quat &q) {
        return quat(q.w, -q.v);
    }

    quat normalize(const quat &q) {
        return quat(q / length(q));
    }

    real_t dot(const quat &q1, const quat &q2) {
        return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
    }

    quat exp(const vec3 &v) {
        real_t theta = length(v);
        if (theta < EPSILON){
            return quat();
        }
        return quat(cos(theta), sin(theta) * (v / theta));
    }

    vec3 log(const quat &q) {
        real_t v_length = length(q.v);
        if (v_length < EPSILON){
            if (q.w > 0.0){
                return vec3();
            }
            else if (q.w < 0.0){
                return vec3(static_cast<real_t>(PI), 0.0, 0.0);
            }
            else{
                return vec3(std::numeric_limits<real_t>::infinity(), std::numeric_limits<real_t>::infinity(), std::numeric_limits<real_t>::infinity());
            }
        }
        else{
            real_t theta = atan2(v_length, q.w);
            return theta * (q.v / v_length);
        }
    }

    quat slerp(const quat &q1, const quat &q2, real_t t) {
        // This is a general form, but commonly not used in practice.
        //return q1 * exp(t * log(inverse(q1) * q2));

        quat _q2 = q2;

        real_t cos_theta = dot(q1, q2);
        // If cos < 0, the interpolation will take the long way.
        // To fix this, one of the orientations must be negated.
        if (cos_theta < 0.0){
            _q2 = -q2;
            cos_theta = -cos_theta;
        }

        // If theta = 0, sin becoming a zero.
        // In this situation, lerp can be used.
        if (1.0 - cos_theta < EPSILON){
            return (1 - t) * q1 + t * _q2;
        }
        else{
            real_t theta = acos(cos_theta);
            return (sin((static_cast<real_t>(1.0) - t) * theta) * q1 + sin(t * theta) * _q2) / sin(theta);
        }
    }
}
