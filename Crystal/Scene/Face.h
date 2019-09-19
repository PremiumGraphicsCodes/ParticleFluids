#pragma once

#include <map>
#include "Vertex.h"
#include <array>

namespace Crystal {
	namespace Math {
		class Triangle3d;
	}
	namespace Scene {

class Face
{
public:
	Face(int v1, int v2, int v3, int id) :
		vertexIds{ v1, v2, v3 },
		id(id),
		materialId(-1)
	{}

	std::array<int, 3> getVertexIds() const { return vertexIds; }

	int getV1() const { return vertexIds[0]; }

	int getV2() const { return vertexIds[1]; }

	int getV3() const { return vertexIds[2]; }

	int getId() const { return id; }

	int materialId;

private:
	int id;
	std::array<int, 3> vertexIds;
};

	}
}