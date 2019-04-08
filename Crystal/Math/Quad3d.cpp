#include "Quad3d.h"

#include "Plane3d.h"

using namespace Crystal::Math;

Plane3d Quad3d::toPlane() const
{
	return Plane3d(origin, getNormal());
}
