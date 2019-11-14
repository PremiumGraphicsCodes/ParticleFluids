#pragma once

#include "IVolume3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Cylinder3d : public IVolume3d
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

	Vector3dd getPosition(const double u, const double v, const double w) const override;

	double getRadius() const { return radius; }

	double getHeight() const { return height; }

	Vector3dd getCenter() const { return center; }

	bool isInside(const Math::Vector3dd& position) const;

private:
	double radius;
	double height;
	Vector3dd center;
};
	}
}