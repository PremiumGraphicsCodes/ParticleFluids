#include "Plane3d.h"

using namespace Crystal::Math;

double Plane3d::getDistance(const Vector3dd& position) const
{
	const auto& v = position - origin;
	return glm::dot(v, normal);
}

bool Plane3d::isSame(const Plane3d& rhs, const double tolerance) const
{
	return
		areSame(origin, rhs.origin, tolerance) &&
		areSame(normal, rhs.normal, tolerance);
}
