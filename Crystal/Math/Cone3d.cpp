#include "Cone3d.h"

using namespace Crystal::Math;

Vector3dd Cone3d::getPosition(const Vector3dd& p) const
{
	const auto uu = p.x * 2.0 * PI;
	const auto r = p.z * radius * (1.0 - p.y);
	const auto x = r * ::cos(uu);
	const auto y = r * ::sin(uu);
	const auto z = p.y * height;
	return bottom + Vector3dd(x, y, z);
}
