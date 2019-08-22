#pragma once

#include <map>
#include "Vertex.h"
#include <array>

namespace Crystal {
	namespace Math {
		class Triangle3d;
	}
	namespace Shape {

class Face
{
public:
	Face(int v1, int v2, int v3, int id = -1) :
		v1(v1),
		v2(v2),
		v3(v3),
		id(id)
	{}

	std::array<int, 3> getVertexIds() const { return { v1,v2,v3 }; }

	int v1;
	int v2;
	int v3;
	int id;

private:
};

	}
}