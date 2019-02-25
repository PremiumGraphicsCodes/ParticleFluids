#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Cone3d
{
public:
	Cone3d() :
		bottom(0,0,0),
		radius(1.0),
		height(1.0)
	{}

	Cone3d(const Vector3dd& bottom, const double radius, const double height) :
		bottom(bottom),
		radius(radius),
		height(height)
	{
	}

	Vector3dd getPosition(const double u, const double v) const
	{
		const auto uu = u * 2.0 * Tolerance<double>::getPI();
		const auto r = radius * (1.0 - v);
		const auto x = r * ::cos(uu);
		const auto y = r * ::sin(uu);
		const auto z = v * height;
		return bottom + Vector3dd(x, y, z);
	}

private:
	Vector3dd bottom;
	double radius;
	double height;
};
	}
}