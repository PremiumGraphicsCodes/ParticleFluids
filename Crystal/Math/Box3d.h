#pragma once

#include "Vector3d.h"
#include "ISolid3d.h"

namespace Crystal {
	namespace Math {
		class Sphere3d;

class Box3d : public ISolid3d
{
public:
	Box3d();

	explicit Box3d(const Vector3dd& point);

	Box3d(const Vector3dd& pointX, const Vector3dd& pointY);

	Box3d getBoundingBox() const { return *this; }

	static Box3d createDegeneratedBox() { return Box3d(Vector3dd(0, 0, 0), Vector3dd(0, 0, 0)); }

	bool isDegenerated() { return start == Vector3dd(0, 0, 0) && end == Vector3dd(0, 0, 0); }

	void add(const Vector3dd& v);

	void add(const Box3d& b);

	double getVolume() const;

	Vector3dd getMax() const { return end; }

	Vector3dd getMin() const { return Vector3dd(getMinX(), getMinY(), getMinZ()); }

	Vector3dd getStart() const { return getMin(); }

	Vector3dd getEnd() const { return getMax(); }

	Vector3dd getCenter() const;

	bool isInside(const Vector3dd& point) const;

	bool isOutside(const Vector3dd& point) const { return !isInside(point); }

	double getMaxX() const { return end.x; }

	double getMinX() const { return start.x; }

	double getMaxY() const { return end.y; }

	double getMinY() const { return start.y; }

	double getMaxZ() const { return end.z; }

	double getMinZ() const { return start.z; }

	Vector3dd getLength() const { return Vector3dd(end.x - getMinX(), end.y - getMinY(), end.z - getMinZ()); }

	bool isSame(const Box3d& rhs, const double tolerance) const;

	bool hasIntersection(const Box3d& rhs) const;

	Box3d getOverlapped(const Box3d& rhs) const;

	Vector3dd getPosition(const double u, const double v, const double w) const override;

	Sphere3d getBoundintSphere() const;

	bool isDegenerated(const double tolerance) { return getVolume() < tolerance; }

	void translate(const Math::Vector3dd& v);

private:
	Vector3dd start;
	Vector3dd end;
};

	}
}