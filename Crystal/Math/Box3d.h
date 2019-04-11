#ifndef __CRYSTAL_MATH_BOX_3D_H__
#define __CRYSTAL_MATH_BOX_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {
		class Space3d;
		class Quad3d;
		class Line3d;

class Box3d
{
public:
	Box3d():
		start(0, 0, 0),
		end(1, 1, 1)
	{
	}

	Box3d(const Vector3dd& point) :
		start(point),
		end(point)
	{}

	Box3d(const Vector3dd& pointX, const Vector3dd& pointY);

	~Box3d() = default;

	static Box3d Unit() {
		return Box3d();
	}

	Box3d getBoundingBox() const { return *this; }

	void add(const Vector3dd& v);

	void add(const Box3d& b);

	double getVolume() const;

	Vector3dd getMax() const { return end; }

	Vector3dd getMin() const { return Vector3dd(getMinX(), getMinY(), getMinZ()); }

	Vector3dd getStart() const { return getMin(); }

	Vector3dd getEnd() const { return getMax(); }

	Vector3dd getCenter() const {
		return Vector3dd(
			(getMinX() + end.x) / 2.0,
			(getMinY() + end.y) / 2.0,
			(getMinZ() + end.z) / 2.0
		);
	}

	bool isInside(const Vector3dd& point) const {
		const bool xIsInterior = (getMinX() < point.x && point.x < end.x);
		const bool yIsInterior = (getMinY() < point.y && point.y < end.y);
		const bool zIsInterior = (getMinZ() < point.z && point.z < end.z);
		return xIsInterior && yIsInterior && zIsInterior;
	}

	bool isOutside(const Vector3dd& point) const { return !isInside(point); }

	double getMaxX() const { return end.x; }

	double getMinX() const { return start.x; }

	double getMaxY() const { return end.y; }

	double getMinY() const { return start.y; }

	double getMaxZ() const { return end.z; }

	double getMinZ() const { return start.z; }

	Vector3dd getLength() const { return Vector3dd(end.x - getMinX(), end.y - getMinY(), end.z - getMinZ()); }

	bool isValid() const { return (getMinX() <= end.x) && (getMinY() <= end.y) && (getMinZ() <= end.z); }

	bool isShirinked() const { return (getMinX() == end.x) && (getMinY() == end.y) && (getMinZ() == end.z); }

	bool isSame(const Box3d& rhs, const double tolerance) const;

	bool hasIntersection(const Box3d& rhs) const;

	Box3d getOverlapped(const Box3d& rhs) const;

	Vector3dd getPosition(const Vector3dd& param) const;

private:
	Vector3dd start;
	Vector3dd end;
};

	}
}

#endif