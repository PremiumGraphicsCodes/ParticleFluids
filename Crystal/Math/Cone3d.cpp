#include "Cone3d.h"

using namespace Crystal::Math;

Vector3dd Cone3d::getPosition(const double u, const double v, const double w) const
{
	const auto uu = u * 2.0 * PI;
	const auto r = w * radius * (1.0 - v);
	const auto x = r * ::cos(uu);
	const auto y = r * ::sin(uu);
	const auto z = v * height;
	return bottom + Vector3dd(x, y, z);
}

bool Cone3d::isInside(const Vector3dd& position) const
{
	assert(false);
	return false;
}
