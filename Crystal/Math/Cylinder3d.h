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

	Vector3dd getPosition(const Vector3dd& p) const override
	{
		const auto theta = p.x * 2.0 * PI;
		const auto x = p.z * radius * ::cos(theta);
		const auto y = p.z * radius * ::sin(theta);
		const auto z = height * p.y - height * 0.5;
		return center + Vector3dd(x, y, z);
	}

private:
	double radius;
	double height;
	Vector3dd center;
};
	}
}