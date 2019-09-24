#pragma once

#include "IVolume.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Cylinder3d : public IVolume
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

	Cylinder3d(const double radius, const double height, const Vector3dd& center);

	Vector3dd getPosition(const Vector3dd& p) const override;

	double getRadius() const { return radius; }

	double getHeight() const { return height; }

	Vector3dd getCenter() const { return center; }

private:
	double radius;
	double height;
	Vector3dd center;
};
	}
}