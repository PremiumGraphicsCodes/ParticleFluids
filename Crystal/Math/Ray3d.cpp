#include "Ray3d.h"

#include "Line3d.h"

using namespace Crystal::Math;

Line3dd Ray3d::toLine(const double length) const
{
	return Line3dd(origin, getPosition(length));
}
