#pragma once

#include <array>
#include "Vector3d.h"
#include "Plane3d.h"

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

	bool isInside(const Vector3dd& p) const;

	Plane3d toPlane() const;

	std::array<Vector3dd, 3> getVertices() const { return vertices; }

private:
	std::array<Vector3dd, 3> vertices;
};

	}
}