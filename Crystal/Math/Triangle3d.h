#pragma once

#include <array>
#include "Vector3d.h"
#include "Matrix3d.h"
#include "Matrix4d.h"

namespace Crystal {
	namespace Math {
		class Plane3d;
		class Box3d;

class Triangle3d
{
public:
	Triangle3d();

	explicit Triangle3d(const std::array<Vector3dd, 3>& vertices);

	Vector3dd getNormal() const;

	double getArea() const;

	bool isInside(const Vector3dd& p) const;

	Plane3d toPlane() const;

	std::array<Vector3dd, 3> getVertices() const { return vertices; }

	void translate(const Math::Vector3dd& v);

	void transform(const Math::Matrix3dd& matrix);

	void transform(const Math::Matrix4dd& matrix);

	Box3d getBoundingBox() const;

private:
	std::array<Vector3dd, 3> vertices;
};

	}
}