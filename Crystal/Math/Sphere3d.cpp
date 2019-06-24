#include "Sphere3d.h"
#include "Box3d.h"

using namespace Crystal::Math;

Sphere3d::Sphere3d(const Box3d& boundingBox)
{
	center = boundingBox.getCenter();
	const auto& length = boundingBox.getLength();
	radius = std::min<double>(std::min<double>(length.x, length.y), length.z) * 0.5;
}

Vector3dd Sphere3d::getPosition(const double r, const double u, const double v) const
{
	const auto theta = 2.0 * u * PI;
	const auto phi = v * PI;
	const auto x = r * radius * std::sin(theta) * std::cos(phi);
	const auto y = r * radius * std::sin(theta) * std::sin(phi);
	const auto z = r * radius * std::cos(theta);
	return center + Vector3dd(x, y, z);
}

Vector3dd Sphere3d::getNormal(const double u, const double v) const
{
	const auto& pos = getPosition(1.0, u, v);
	return glm::normalize(pos - center);
}

bool Sphere3d::isSame(const Sphere3d& rhs, const double tolerance) const
{
	return
		::isEqual(radius, rhs.radius, tolerance) &&
		(center == rhs.center);
}
