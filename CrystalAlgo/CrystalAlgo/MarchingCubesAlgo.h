#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "MCCell.h"

namespace Crystal {
	namespace Algo {
		class Volume;

class MarchingCubesAlgo
{
public:

	int build(const Volume& volume, const double isoLevel);

	int march(const MCCell& cell, const double isoLevel);

	std::vector<Math::Triangle3d> getTriangles() const { return triangles; }

private:
	Math::Vector3dd getInterpolatedPosition(const double isolevel, const MCCell::Vertex& v1, const MCCell::Vertex& v2);

	std::vector<Math::Triangle3d> triangles;
};
	}
}
