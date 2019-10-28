#ifndef __CRYSTAL_MATH_BOX_3D_H__
#define __CRYSTAL_MATH_BOX_3D_H__

#include "Vector3d.h"
#include "IVolume3d.h"

namespace Crystal {
	namespace Math {
		class Space3d;
		class Quad3d;
		class Line3d;
		class Sphere3d;

class Box3d : IVolume3d
{
public:
	Box3d();

	explicit Box3d(const Vector3dd& point);

	Box3d(const Vector3dd& pointX, const Vector3dd& pointY);

	Box3d getBoundingBox() const { return *this; }

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

	Vector3dd getPosition(const Vector3dd& param) const;

	Vector3dd getNormal(const Math::Vector2dd& p) const override
	{
		return getPosition(Vector3dd(p, 1.0) - Vector3dd(p, 0.0));
	}

	Sphere3d getBoundintSphere() const;

private:
	Vector3dd start;
	Vector3dd end;
};

	}
}

#endif