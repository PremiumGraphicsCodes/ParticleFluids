#pragma once

#include "Vector3d.h"
#include "IVolume3d.h"

namespace Crystal {
	namespace Math {
		class Sphere3d;

class Box3d : public IVolume3d
{
public:
	Box3d();

	explicit Box3d(const Vector3dd& point);

	Box3d(const Vector3dd& pointX, const Vector3dd& pointY);

	Box3d getBoundingBox() const { return *this; }

	static Box3d createDegeneratedBox();

	bool isDegenerated() const;

	void add(const Vector3dd& v);

	void add(const Box3d& b);

	double getVolume() const;

	Vector3dd getMax() const { return max; }

	Vector3dd getMin() const { return min; }

	Vector3dd getStart() const { return getMin(); }

	Vector3dd getEnd() const { return getMax(); }

	Vector3dd getCenter() const;

	bool isInside(const Vector3dd& point) const;

	bool isOutside(const Vector3dd& point) const { return !isInside(point); }

	double getMaxX() const { return max.x; }

	double getMinX() const { return min.x; }

	double getMaxY() const { return max.y; }

	double getMinY() const { return min.y; }

	double getMaxZ() const { return max.z; }

	double getMinZ() const { return min.z; }

	Vector3dd getLength() const { return Vector3dd(max.x - getMinX(), max.y - getMinY(), max.z - getMinZ()); }

	bool isSame(const Box3d& rhs, const double tolerance) const;

	bool hasIntersection(const Box3d& rhs) const;

	Box3d getOverlapped(const Box3d& rhs) const;

	Vector3dd getPosition(const double u, const double v, const double w) const override;

	Sphere3d getBoundintSphere() const;

	bool isDegenerated(const double tolerance) { return getVolume() < tolerance; }

	void translate(const Math::Vector3dd& v);

private:
	Vector3dd min;
	Vector3dd max;
};

	}
}