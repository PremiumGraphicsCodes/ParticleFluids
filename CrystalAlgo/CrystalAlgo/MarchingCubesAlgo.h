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

	int build(const Volume3d& volume);

	int march(const MCCell& cell, const double isolevel);

	std::vector<Math::Triangle3d> getTriangles() const { return triangles; }

private:
	/*
	Linearly interpolate the position where an isosurface cuts
	an edge between two vertices, each with their own scalar value
	*/
	Math::Vector3dd getInterpolatedPosition(double isolevel, const Math::Vector3dd& p1, const Math::Vector3dd& p2, double valp1, double valp2);

	std::vector<Math::Triangle3d> triangles;
};
	}
}
