#pragma once

#include <array>
#include "../Math/Vector3d.h"
#include "../Math/Triangle3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Scene {

class TriangleFace
{
public:
	explicit TriangleFace(const std::array<Math::Vector3dd, 3>& vertices);

	TriangleFace(const std::array<Math::Vector3dd, 3>& vertices, const Math::Vector3dd& normal) :
		vertices(vertices),
		normal(normal)
	{}

	Math::Vector3dd getNormal() const { return normal; }

	std::array<Math::Vector3dd, 3> getVertices() const { return vertices; }

	Math::Triangle3d toTriangle() const { return Math::Triangle3d(vertices); }

	void translate(const Math::Vector3dd& v);

	void transform(const Math::Matrix3dd& m);

	void transform(const Math::Matrix4dd& m);

private:
	std::array<Math::Vector3dd, 3> vertices;
	Math::Vector3dd normal;
};

	}
}