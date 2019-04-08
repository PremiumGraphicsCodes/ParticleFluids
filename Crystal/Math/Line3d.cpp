#include "Line3d.h"

#include "Ray3d.h"

using namespace Crystal::Math;

Ray3d Line3dd::toRay() const
{
	return Ray3d(origin, getDirection());
}
