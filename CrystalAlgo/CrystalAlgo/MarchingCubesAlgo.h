#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Algo {
		class Volume3d;

class MarchingCubesAlgo
{
public:
	struct MCCell
	{
		/*
		MCCell(const Math::Box3d& box) {
		}
		*/

		std::array<Math::Vector3dd, 8> position;
		std::array<double, 8> value;
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
