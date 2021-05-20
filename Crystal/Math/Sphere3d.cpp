#include "Sphere3d.h"
#include "Box3d.h"

#include <numeric>
#include "Tolerance.h"

using namespace Crystal::Math;

Sphere3d::Sphere3d() :
	center(Vector3dd(0, 0, 0)),
	radius(1.0)
{}

Sphere3d::Sphere3d(const Vector3dd& center, const double radius) :
	center(center),
	radius(radius)
{}

Sphere3d::Sphere3d(const Box3dd& boundingBox)
{
	center = boundingBox.getCenter();
	const auto& length = boundingBox.getLength();
	radius = std::min<double>(std::min<double>(length.x, length.y), length.z) * 0.5;
}

Vector3dd Sphere3d::getPosition(const double u, const double v) const
{
	return getPosition(u, v, 1.0);
}

Vector3dd Sphere3d::getPosition(const double u, const double v, const double w) const
{
	const auto theta = u * PI;
	const auto phi = 2.0 * v * PI;
	const auto x = w * radius * std::sin(theta) * std::cos(phi);
	const auto y = w * radius * std::sin(theta) * std::sin(phi);
	const auto z = w * radius * std::cos(theta);
	return center + Vector3dd(x, y, z);
}

Vector3dd Sphere3d::getNormal(const double u, const double v) const
{
	const auto& pos = getPosition(u, v, 1.0);
	return glm::normalize(pos - center);
}

bool Sphere3d::isSame(const Sphere3d& rhs, const double tolerance) const
{
	return
		::isEqual(radius, rhs.radius, tolerance) &&
		(center == rhs.center);
}

Box3dd Sphere3d::getBoundingBox() const
{
	const auto min = center - Vector3dd(radius, radius, radius);
	const auto max = center + Vector3dd(radius, radius, radius);
	return Box3dd(min, max);
}
