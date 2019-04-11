#include "Triangle3d.h"

#include "Plane3d.h"

using namespace Crystal::Math;

Vector3dd Triangle3d::getNormal() const
{
	const auto v1 = vertices[1] - vertices[0];
	const auto v2 = vertices[2] - vertices[0];
	return glm::normalize(glm::cross(v1, v2));
}

double Triangle3d::getArea() const
{
	const auto v1 = vertices[1] - vertices[0];
	const auto v2 = vertices[2] - vertices[0];
	return glm::length(glm::cross(v1, v2))  * 0.5;
}

bool Triangle3d::isInside(const Vector3dd& p) const
{
	const auto& n = getNormal();

	const auto a = vertices[0] - p;
	const auto b = vertices[1] - p;
	const auto c = vertices[2] - p;

	const auto d = vertices[1] - vertices[0];
	const auto e = vertices[2] - vertices[1];
	const auto f = vertices[0] - vertices[2];

	const auto& v1 = glm::cross(a, d);
	if (glm::dot(v1, n) < 0.0) {
		return false;
	}
	const auto& v2 = glm::cross(b, e);
	if (glm::dot(v2, n) < 0.0) {
		return false;
	}
	const auto& v3 = glm::cross(c, f);
	if (glm::dot(v3, n) < 0.0) {
		return false;
	}
	return true;
}

Plane3d Triangle3d::toPlane() const
{
	return Plane3d(vertices[0], getNormal());
}

