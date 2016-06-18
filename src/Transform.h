#pragma once

struct QTransform;

struct Transform{
	Matrix m;
	Vector v;

	Transform() { }
	Transform(const Matrix &m, const Vector &v) : m(m), v(v) { }

	friend Transform		operator * (const Transform &t1, const Transform &t2);
	friend Vector			operator * (const Transform &t, const Vector &v);
	friend Point			operator * (const Transform &t, const Point &p);
	friend std::ostream&	operator << (std::ostream &stream, const Transform &t);
	friend std::istream&	operator >> (std::istream &stream, Transform &t);

	static Transform		scale(real_t x, real_t y, real_t z);
	static Transform		rotate(real_t theta, const Vector &direction);
	static Transform		translate(real_t x, real_t y, real_t z);

	friend QTransform		TransformToQTransform(const Transform &t);
	friend Transform		QTransformToTransform(const QTransform &qt);
};

struct QTransform{
	Quater q;
	Vector v;

	QTransform() { }
	QTransform(const Quater &q, const Vector &v) : q(q), v(v) { }

	friend QTransform		operator * (const QTransform &t1, const QTransform &t2);
	friend Vector			operator * (const QTransform &t, const Vector &v);
	friend Point			operator * (const QTransform &t, const Point &p);
	friend std::ostream&	operator << (std::ostream &stream, const QTransform &t);
	friend std::istream&	operator >> (std::istream &stream, QTransform &t);

	static QTransform		rotate(real_t theta, const Vector &direction);
	static QTransform		rotate(const Vector &v);
	static QTransform		translate(real_t x, real_t y, real_t z);
	static QTransform		translate(const Vector &v);

	friend QTransform		TransformToQTransform(const Transform &t);
	friend Transform		QTransformToTransform(const QTransform &qt);
};