#pragma once

#include <array>
#include "Vector3d.h"

namespace Crystal {
	namespace Math {
		class Plane3d;

class Triangle3d
{
public:
	explicit Triangle3d(const std::array<Vector3dd, 3>& vertices) :
		vertices(vertices)
	{}

	Vector3dd getNormal() const;

	double getArea() const;

	bool isInside(const Vector3dd& p) const;

	Plane3d toPlane() const;

	std::array<Vector3dd, 3> getVertices() const { return vertices; }

private:
	std::array<Vector3dd, 3> vertices;
};

	}
}