#pragma once

#include "IVolume3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Cone3d : public IVolume3d
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

	Vector3dd getPosition(const Vector3dd& p) const override;

	Vector3dd getBottom() const { return bottom; }

	double getRadius() const { return radius; }

	double getHeight() const { return height; }

private:
	Vector3dd bottom;
	double radius;
	double height;
};
	}
}