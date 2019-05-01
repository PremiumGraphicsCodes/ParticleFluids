#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"

namespace Crystal {
	namespace Algo {
		class Volume3d;

class MarchingCubesAlgo
{
public:
	struct MCCell
	{
		Math::Vector3dd position[8];
		double value[8];
	};

	int build(const Volume3d& volume, const double isoLevel);

	int march(const MCCell& cell, const double isoLevel);

	std::vector<Math::Triangle3d> getTriangles() const { return triangles; }

private:
	Math::Vector3dd getInterpolatedPosition(const double isolevel, const Math::Vector3dd& p1, const Math::Vector3dd& p2, const double valp1, const double valp2);

	std::vector<Math::Triangle3d> triangles;
};
	}
}
