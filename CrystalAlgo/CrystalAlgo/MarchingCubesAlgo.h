#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"

namespace Crystal {
	namespace Algo {

class MarchingCubesAlgo
{
public:
	struct MCCell
	{
		Math::Vector3dd p[8];
		double val[8];
	};

	/*
		Given a grid cell and an isolevel, calculate the triangular
		facets required to represent the isosurface through the cell.
		Return the number of triangular facets, the array "triangles"
		will be loaded up with the vertices at most 5 triangular facets.
		0 will be returned if the grid cell is either totally above
		of totally below the isolevel.
	*/
	int march(const MCCell& cell, const double isolevel);

	std::vector<Math::Triangle3d> getTriangles() const { return triangles; }

private:
	/*
	Linearly interpolate the position where an isosurface cuts
	an edge between two vertices, each with their own scalar value
	*/
	Math::Vector3dd VertexInterp(double isolevel, const Math::Vector3dd& p1, const Math::Vector3dd& p2, double valp1, double valp2);

	std::vector<Math::Triangle3d> triangles;
};
	}
}
