#include "Line3d.h"

#include "Ray3d.h"

using namespace Crystal::Math;

Ray3d Line3dd::toRay() const
{
	const auto& direction = glm::normalize(getDirection());
	return Ray3d(origin, direction);
}
