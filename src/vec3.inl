namespace tfm{
    template <typename type_t>
    type_t& tvec3<type_t>::operator [] (int i) {
        assert(0 <= i && i <= 2);
        return *(&x + i);
    }

    template <typename type_t>
    type_t tvec3<type_t>::operator [] (int i) const {
        assert(0 <= i && i <= 2);
        return *(&x + i);
    }

    // -v
    template <typename type_t>
    tvec3<type_t> tvec3<type_t>::operator - () const{
        return tvec3<type_t>(-(this->x), -(this->y), -(this->z));
    }

    // v1 + v2
    template <typename type_t>
    tvec3<type_t> tvec3<type_t>::operator + (const tvec3<type_t> &v) const {
        return tvec3<type_t>(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    // v1 - v2
    template <typename type_t>
    tvec3<type_t> tvec3<type_t>::operator - (const tvec3<type_t> &v) const {
        return tvec3<type_t>(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    // v1 .* v2
    template <typename type_t>
    tvec3<type_t> tvec3<type_t>::operator * (const tvec3<type_t> &v) const {
        return tvec3<type_t>(this->x * v.x, this->y * v.y, this->z * v.z);
    }

    // v * k
    template <typename type_t>
    tvec3<type_t> tvec3<type_t>::operator * (type_t k) const {
        return tvec3<type_t>(this->x * k, this->y * k, this->z * k);
    }

    // v / k
    template <typename type_t>
    tvec3<type_t> tvec3<type_t>::operator / (type_t k) const {
        return tvec3<type_t>(this->x / k, this->y / k, this->z / k);
    }

    // v1 += v2
    template <typename type_t>
    tvec3<type_t>& tvec3<type_t>::operator += (const tvec3<type_t> &v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }

    // v1 -= v2
    template <typename type_t>
    tvec3<type_t>& tvec3<type_t>::operator -= (const tvec3<type_t> &v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }

    // v += k
    template <typename type_t>
    tvec3<type_t>& tvec3<type_t>::operator += (type_t k) {
        this->x += k;
        this->y += k;
        this->z += k;
        return *this;
    }

    // v -= k
    template <typename type_t>
    tvec3<type_t>& tvec3<type_t>::operator -= (type_t k) {
        this->x -= k;
        this->y -= k;
        this->z -= k;
        return *this;
    }

    // v1 .*= v2
    template <typename type_t>
    tvec3<type_t>& tvec3<type_t>::operator *= (const tvec3<type_t> &v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    // v *= k
    template <typename type_t>
    tvec3<type_t>& tvec3<type_t>::operator *= (type_t k){
        this->x *= k;
        this->y *= k;
        this->z *= k;
        return *this;
    }

    // v /= k
    template <typename type_t>
    tvec3<type_t>& tvec3<type_t>::operator /= (type_t k){
        assert(k != 0.0);
        this->x /= k;
        this->y /= k;
        this->z /= k;
        return *this;
    }

    // k * v
    template <typename type_t>
    tvec3<type_t> operator * (type_t k, const tvec3<type_t> &v){
        return tvec3<type_t>(v.x * k, v.y * k, v.z * k);
    }

    template <typename type_t>
    std::ostream& operator << (std::ostream &stream, const tvec3<type_t> &v){
        stream << std::fixed << std::setprecision(2) << std::setfill('0');
        stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return stream;
    }

    template <typename type_t>
    std::istream& operator >> (std::istream &stream, tvec3<type_t> &v){
        stream >> v.x >> v.y >> v.z;
        return stream;
    }

    template <typename type_t>
    type_t isqrt(const tvec3<type_t> &v) {
        // Source codes from Quake3
        
        float number = float(v.x * v.x + v.y * v.y + v.z * v.z);
        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        y = number;
        i = *(long *)&y;						// evil floating point bit level hacking
        i = 0x5f3759df - (i >> 1);				// what the fuck? 
        y = *(float *)&i;
        y = y * (threehalfs - (x2 * y * y));	// 1st iteration
        //y = y * (threehalfs - (x2 * y * y));	// 2nd iteration, this can be removed

        return static_cast<type_t>(y);
    }

    template <typename type_t>
    type_t length(const tvec3<type_t> &v) {
        return static_cast<type_t>(sqrt(dot(v, v)));
    }

    template <typename type_t>
    type_t sqrLength(const tvec3<type_t> &v) {
        return dot(v, v);
    }

    template <typename type_t>
    tvec3<type_t> normalize(const tvec3<type_t> &v){
        //real_t l = length(v);
        //return tvec3<type_t>(v.x / l, v.y / l, v.z / l);
        return v * isqrt(v);
    }

    template <typename type_t>
    type_t dot(const tvec3<type_t> &v1, const tvec3<type_t> &v2) {
        return static_cast<type_t>(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    }

    template <typename type_t>
    tvec3<type_t> cross(const tvec3<type_t> &v1, const tvec3<type_t> &v2) {
        return tvec3<type_t>(v1.y * v2.z - v1.z * v2.y,
                            v1.z * v2.x - v1.x * v2.z,
                            v1.x * v2.y - v1.y * v2.x);
    }
}
