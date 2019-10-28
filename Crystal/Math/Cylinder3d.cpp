#include "Cylinder3d.h"

using namespace Crystal::Math;

Cylinder3d::Cylinder3d(const double radius, const double height, const Vector3dd& center) :
	radius(radius),
	height(height),
	center(center)
{
}

Vector3dd Cylinder3d::getPosition(const Vector3dd& p) const
{
	const auto theta = p.x * 2.0 * PI;
	const auto x = p.z * radius * ::cos(theta);
	const auto y = p.z * radius * ::sin(theta);
	const auto z = height * p.y - height * 0.5;
	return center + Vector3dd(x, y, z);
}

bool Cylinder3d::isInside(const Vector3dd& position) const
{
	assert(false);
	return false;
}
