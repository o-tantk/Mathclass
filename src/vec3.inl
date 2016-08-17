namespace tfm{
    template <typename T>
    T& tvec3<T>::operator [] (int i) {
        assert(0 <= i && i <= 2);
        return *(&x + i);
    }

    template <typename T>
    T tvec3<T>::operator [] (int i) const {
        assert(0 <= i && i <= 2);
        return *(&x + i);
    }

    template <typename T>
    tvec3<T> operator - (const tvec3<T> &v){
        return tvec3<T>(-(v.x), -(v.y), -(v.z));
    }

    template <typename T>
    tvec3<T> operator + (const tvec3<T> &v1, const tvec3<T> &v2){
        return tvec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    template <typename T>
    tvec3<T> operator - (const tvec3<T> &v1, const tvec3<T> &v2){
        return tvec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    template <typename T>
    tvec3<T> operator * (const tvec3<T> &v1, const tvec3<T> &v2) {
        return tvec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    template <typename T>
    tvec3<T> operator * (const tvec3<T> &v, T k){
        return tvec3<T>(v.x * k, v.y * k, v.z * k);
    }

    template <typename T>
    tvec3<T> operator * (T k, const tvec3<T> &v){
        return tvec3<T>(v.x * k, v.y * k, v.z * k);
    }

    template <typename T>
    tvec3<T> operator / (const tvec3<T> &v, T k){
        return tvec3<T>(v.x / k, v.y / k, v.z / k);
    }

    template <typename T>
    tvec3<T>& operator += (tvec3<T> &v1, const tvec3<T> &v2){
        v1.x += v2.x;
        v1.y += v2.y;
        v1.z += v2.z;
        return v1;
    }

    template <typename T>
    tvec3<T>& operator -= (tvec3<T> &v1, const tvec3<T> &v2){
        v1.x -= v2.x;
        v1.y -= v2.y;
        v1.z -= v2.z;
        return v1;
    }

    template <typename T>
    tvec3<T>&	operator += (tvec3<T> &v, T k){
        v.x += k;
        v.y += k;
        v.z += k;
        return v;
    }

    template <typename T>
    tvec3<T>& operator -= (tvec3<T> &v, T k){
        v.x -= k;
        v.y -= k;
        v.z -= k;
        return v;
    }

    template <typename T>
    tvec3<T>& operator *= (tvec3<T> &v1, const tvec3<T> &v2) {
        v1.x *= v2.x;
        v1.y *= v2.y;
        v1.z *= v2.z;
        return v1;
    }

    template <typename T>
    tvec3<T>&	operator *= (tvec3<T> &v, T k){
        v.x *= k;
        v.y *= k;
        v.z *= k;
        return v;
    }

    template <typename T>
    tvec3<T>& operator /= (tvec3<T> &v, T k){
        assert(k != 0.0);
        v.x /= k;
        v.y /= k;
        v.z /= k;
        return v;
    }

    template <typename T>
    std::ostream& operator << (std::ostream &stream, const tvec3<T> &v){
        stream << std::fixed << std::setprecision(2) << std::setfill('0');
        stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return stream;
    }

    template <typename T>
    std::istream& operator >> (std::istream &stream, tvec3<T> &v){
        stream >> v.x >> v.y >> v.z;
        return stream;
    }

    template <typename T>
    T isqrt(const tvec3<T> &v) {
        // Source codes from Quake3
        
        float number = v.x * v.x + v.y * v.y + v.z * v.z;
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

        return T(y);
    }

    template <typename T>
    T length(const tvec3<T> &v){
        return T(sqrt(dot(v, v)));
    }

    template <typename T>
    tvec3<T> normalize(const tvec3<T> &v){
        //real_t l = length(v);
        //return tvec3<T>(v.x / l, v.y / l, v.z / l);
        return v * isqrt(v);
    }

    template <typename T>
    T dot(const tvec3<T> &v1, const tvec3<T> &v2){
        return T(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    }

    template <typename T>
    tvec3<T> cross(const tvec3<T> &v1, const tvec3<T> &v2){
        return tvec3<T>(v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x);
    }
}
