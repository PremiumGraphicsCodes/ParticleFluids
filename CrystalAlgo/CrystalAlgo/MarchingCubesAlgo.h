#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Algo {
		class Volume;

class MarchingCubesAlgo
{
public:
	struct MCCell
	{
		struct Vertex
		{
			Vertex()
			{}

			Vertex(const Math::Vector3dd& position, double value) :
				position(position),
				value(value)
			{}

			Math::Vector3dd position;
			double value;
		};

		MCCell()
		{}

		explicit MCCell(const std::array<Vertex, 8>& vertices) :
			vertices(vertices)
		{
		}

		std::array<Vertex, 8> vertices;
	};

	int build(const Volume& volume, const double isoLevel);

	int march(const MCCell& cell, const double isoLevel);

	std::vector<Math::Triangle3d> getTriangles() const { return triangles; }

private:
	Math::Vector3dd getInterpolatedPosition(const double isolevel, const MCCell::Vertex& v1, const MCCell::Vertex& v2);

	std::vector<Math::Triangle3d> triangles;
};
	}
}
