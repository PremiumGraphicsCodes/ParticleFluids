#include "Line3d.h"
#include "Ray3d.h"

using namespace Crystal::Math;

Line3dd::Line3dd() :
	origin(0, 0, 0),
	dir(1, 0, 0)
{
}

Line3dd::Line3dd(const Vector3dd& origin, const Vector3dd& dir) :
	origin(origin),
	dir(dir)
{
}

Line3dd Line3dd::fromPoints(const Vector3dd& start, const Vector3dd& end)
{
	return Line3dd(start, end - start);
}

void Line3dd::transform(const Matrix3dd& m)
{
	origin = m * origin;
	dir = m * dir;
}

void Line3dd::transform(const Matrix4dd& m)
{
	origin = m * glm::vec4(origin, 1.0);
	dir = m * glm::vec4(dir, 1.0);
}

Vector3dd Line3dd::getPosition(const double u) const
{
	return origin + dir * u;
}

bool Line3dd::isSame(const Line3dd& rhs, const double tolerance) const
{
	return
		areSame(origin, rhs.getStart(), tolerance) &&
		areSame(dir, rhs.getDirection(), tolerance);
}

Ray3d Line3dd::toRay() const
{
	const auto& direction = glm::normalize(getDirection());
	return Ray3d(origin, direction);
}
