#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Plane3d
{
public:
	Plane3d() :
		origin(0, 0, 0),
		normal(0, 0, 1)
	{
	}

	Plane3d(const Vector3dd& origin, const Vector3dd& normal) :
		origin(origin),
		normal(normal)
	{
	}

	Vector3dd getOrigin() const { return origin; }

	Vector3dd getNormal() const { return normal; }

	double getDistance(const Vector3dd& position) const;

	bool isSame(const Plane3d& rhs, const double tolerance) const;

private:
	Vector3dd origin;
	Vector3dd normal;
};

	}
}