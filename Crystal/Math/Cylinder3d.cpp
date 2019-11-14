#include "Cylinder3d.h"

using namespace Crystal::Math;

Cylinder3d::Cylinder3d(const double radius, const double height, const Vector3dd& center) :
	radius(radius),
	height(height),
	center(center)
{
}

Vector3dd Cylinder3d::getPosition(const double u, const double v, const double w) const
{
	const auto theta = u * 2.0 * PI;
	const auto x = w * radius * ::cos(theta);
	const auto y = w * radius * ::sin(theta);
	const auto z = height * v - height * 0.5;
	return center + Vector3dd(x, y, z);
}

bool Cylinder3d::isInside(const Vector3dd& position) const
{
	assert(false);
	return false;
}
