#pragma once

#include "ICurve3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Cylinder3d : public ICurve3d
{
public:
	Cylinder3d() :
		Cylinder3d(1.0)
	{
	}

	explicit Cylinder3d(const double radius) :
		Cylinder3d(radius, 1.0)
	{
	}

	Cylinder3d(const double radius, const double height) :
		Cylinder3d(radius, height, Vector3dd(0,0,0))
	{}

	Cylinder3d(const double radius, const double height, const Vector3dd& center) :
		radius(radius),
		height(height),
		center(center)
	{
	}

	Vector3dd getPosition(const double r, const double u, const double v) const override
	{
		const auto theta = u * 2.0 * PI;
		const auto x = r * radius * ::cos(theta);
		const auto y = r * radius * ::sin(theta);
		const auto z = height * v - height * 0.5;
		return center + Vector3dd(x, y, z);
	}

private:
	double radius;
	double height;
	Vector3dd center;
};
	}
}