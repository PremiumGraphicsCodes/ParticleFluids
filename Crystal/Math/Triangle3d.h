#pragma once

#include <array>
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Triangle3d
{
public:
	explicit Triangle3d(const std::array<Vector3dd, 3>& vertices) :
		vertices(vertices)
	{}

	Vector3dd getNormal() const {
		const auto v1 = vertices[1] - vertices[0];
		const auto v2 = vertices[2] - vertices[0];
		return glm::normalize(glm::cross(v1, v2));
	}

	double getArea() const {
		const auto v1 = vertices[1] - vertices[0];
		const auto v2 = vertices[2] - vertices[0];
		return glm::length( glm::cross(v1, v2) )  * 0.5;
	}

	bool isInside(const Vector3dd& p) const
	{
		const auto& normal = getNormal();

		const auto a = vertices[0] - p;
		const auto b = vertices[1] - p;
		const auto c = vertices[2] - p;

		const auto p0ToP1 = vertices[1] - vertices[0];
		const auto p1ToP2 = vertices[2] - vertices[1];
		const auto p2ToP0 = vertices[0] - vertices[2];

		const auto& v1 = glm::cross(a, p0ToP1);
		if (glm::dot(v1, normal) < 0.0) {
			return false;
		}
		const auto& v2 = glm::cross(b, p1ToP2);
		if (glm::dot(v2, normal) < 0.0) {
			return false;
		}
		const auto& v3 = glm::cross(c, p2ToP0);
		if (glm::dot(v3, normal) < 0.0) {
			return false;
		}
		return true;
	}

	std::array<Vector3dd, 3> getVertices() const { return vertices; }

private:
	std::array<Vector3dd, 3> vertices;
};

	}
}