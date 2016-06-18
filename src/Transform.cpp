#include "Mathclass.h"

// Transform //////////////////////////////////////////////////////////

Transform operator * (const Transform &t1, const Transform &t2) {
	return Transform(t1.m * t2.m, t1.m * t2.v + t1.v);
}

Vector operator * (const Transform &t, const Vector &v) {
	return t.m * v;
}

Point operator * (const Transform &t, const Point &p) {
	return t.m * p + t.v;
}

std::ostream& operator << (std::ostream &stream, const Transform &t) {
	stream << t.m << " " << t.v;
	return stream;
}

std::istream& operator >> (std::istream &stream, Transform &t) {
	stream >> t.m >> t.v;
	return stream;
}

Transform Transform::scale(real_t x, real_t y, real_t z) {
	return Transform(Matrix(x, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, z), Vector());
}

Transform Transform::rotate(real_t theta, const Vector &direction) {
	real_t l = length(direction);
	if (theta == 0.0 || l == 0.0){
		return Transform();
	}
	Vector u = direction / l;
	Matrix vvt(u.x * u.x, u.x * u.y, u.x * u.z,
				u.y * u.x, u.y * u.y, u.y * u.z,
				u.z * u.x, u.z * u.y, u.z * u.z);
	Matrix vx(0.0, -u.z, u.y,
			u.z, 0.0, -u.x,
			-u.y, u.x, 0.0);
	Matrix r = vvt + cos(theta) * (Matrix() - vvt) + sin(theta) * vx;
	return Transform(r, Vector());
}

Transform Transform::translate(real_t x, real_t y, real_t z) {
	return Transform(Matrix(), Vector(x, y, z));
}

// TransformQ //////////////////////////////////////////////////////////

QTransform operator * (const QTransform &t1, const QTransform &t2) {
	return QTransform(t1.q * t2.q, (t1.q * Quater(0, t2.v) * inverse(t1.q)).v + t1.v);
}

Vector operator * (const QTransform &t, const Vector &v) {
	return (t.q * Quater(0, v) * inverse(t.q)).v;
}

Point operator * (const QTransform &t, const Point &p) {
	return Point((t.q * Quater(0, Vector(p)) * inverse(t.q)).v) + t.v;
}

std::ostream& operator << (std::ostream &stream, const QTransform &t) {
	stream << t.q << " " << t.v;
	return stream;
}

std::istream& operator >> (std::istream &stream, QTransform &t) {
	stream >> t.q >> t.v;
	return stream;
}

QTransform QTransform::rotate(real_t theta, const Vector &direction) {
	real_t l = length(direction);
	if (theta == 0.0 || l == 0.0){
		return QTransform();
	}
	return QTransform(exp(0.5 * theta * (direction / l)), Vector());
}

QTransform QTransform::rotate(const Vector &v) {
	if (length(v) == 0.0){
		return QTransform();
	}
	return QTransform(exp(0.5 * v), Vector());
}

QTransform QTransform::translate(real_t x, real_t y, real_t z) {
	return QTransform(Quater(), Vector(x, y, z));
}

QTransform QTransform::translate(const Vector &v) {
	return QTransform(Quater(), v);
}

QTransform TransformToQTransform(const Transform &t) {
	return QTransform(normalize(MatrixToQuater(t.m)), t.v);
}

Transform QTransformToTransform(const QTransform &qt) {
	return Transform(QuaterToMatrix(qt.q), qt.v);
}
