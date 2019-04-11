#pragma once

#include "ICurve3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Cone3d : public ICurve3d
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

	Vector3dd getPosition(const double u, const double v) const override;

private:
	Vector3dd bottom;
	double radius;
	double height;
};
	}
}