//from http://paulbourke.net/geometry/polygonise/

#include "../../Crystal/Math/Vector3d.h"
#include "MarchingCubesAlgo.h"
#include "MarchingCubesTable.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;
using namespace Crystal::Algo::MarchingCubesTable;

/*
   Linearly interpolate the position where an isosurface cuts
   an edge between two vertices, each with their own scalar value
*/
Vector3dd MarchingCubesAlgo::VertexInterp(double isolevel, const Vector3dd& p1, const Vector3dd& p2, double valp1, double valp2)
{
	double mu;
	Vector3dd p;

	if (::fabs(isolevel - valp1) < 0.00001)
		return(p1);
	if (::fabs(isolevel - valp2) < 0.00001)
		return(p2);
	if (::fabs(valp1 - valp2) < 0.00001)
		return(p1);
	mu = (isolevel - valp1) / (valp2 - valp1);
	p.x = p1.x + mu * (p2.x - p1.x);
	p.y = p1.y + mu * (p2.y - p1.y);
	p.z = p1.z + mu * (p2.z - p1.z);

	return(p);
}

/*
   Given a grid cell and an isolevel, calculate the triangular
   facets required to represent the isosurface through the cell.
   Return the number of triangular facets, the array "triangles"
   will be loaded up with the vertices at most 5 triangular facets.
	0 will be returned if the grid cell is either totally above
   of totally below the isolevel.
*/
int MarchingCubesAlgo::march(const MCCell& cell, const double isolevel)
{
	Vector3dd vertlist[12];


	/*
	   Determine the index into the edge table which
	   tells us which vertices are inside of the surface
	*/
	int cubeindex = 0;
	if (cell.val[0] < isolevel) cubeindex |= 1;
	if (cell.val[1] < isolevel) cubeindex |= 2;
	if (cell.val[2] < isolevel) cubeindex |= 4;
	if (cell.val[3] < isolevel) cubeindex |= 8;
	if (cell.val[4] < isolevel) cubeindex |= 16;
	if (cell.val[5] < isolevel) cubeindex |= 32;
	if (cell.val[6] < isolevel) cubeindex |= 64;
	if (cell.val[7] < isolevel) cubeindex |= 128;

	/* Cube is entirely in/out of the surface */
	if (edgeTable[cubeindex] == 0)
		return(0);

	/* Find the vertices where the surface intersects the cube */
	if (edgeTable[cubeindex] & 1)
		vertlist[0] =
		VertexInterp(isolevel, cell.p[0], cell.p[1], cell.val[0], cell.val[1]);
	if (edgeTable[cubeindex] & 2)
		vertlist[1] =
		VertexInterp(isolevel, cell.p[1], cell.p[2], cell.val[1], cell.val[2]);
	if (edgeTable[cubeindex] & 4)
		vertlist[2] =
		VertexInterp(isolevel, cell.p[2], cell.p[3], cell.val[2], cell.val[3]);
	if (edgeTable[cubeindex] & 8)
		vertlist[3] =
		VertexInterp(isolevel, cell.p[3], cell.p[0], cell.val[3], cell.val[0]);
	if (edgeTable[cubeindex] & 16)
		vertlist[4] =
		VertexInterp(isolevel, cell.p[4], cell.p[5], cell.val[4], cell.val[5]);
	if (edgeTable[cubeindex] & 32)
		vertlist[5] =
		VertexInterp(isolevel, cell.p[5], cell.p[6], cell.val[5], cell.val[6]);
	if (edgeTable[cubeindex] & 64)
		vertlist[6] =
		VertexInterp(isolevel, cell.p[6], cell.p[7], cell.val[6], cell.val[7]);
	if (edgeTable[cubeindex] & 128)
		vertlist[7] =
		VertexInterp(isolevel, cell.p[7], cell.p[4], cell.val[7], cell.val[4]);
	if (edgeTable[cubeindex] & 256)
		vertlist[8] =
		VertexInterp(isolevel, cell.p[0], cell.p[4], cell.val[0], cell.val[4]);
	if (edgeTable[cubeindex] & 512)
		vertlist[9] =
		VertexInterp(isolevel, cell.p[1], cell.p[5], cell.val[1], cell.val[5]);
	if (edgeTable[cubeindex] & 1024)
		vertlist[10] =
		VertexInterp(isolevel, cell.p[2], cell.p[6], cell.val[2], cell.val[6]);
	if (edgeTable[cubeindex] & 2048)
		vertlist[11] =
		VertexInterp(isolevel, cell.p[3], cell.p[7], cell.val[3], cell.val[7]);

	/* Create the triangle */
	int ntriang = 0;
	for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
		const auto& v0 = vertlist[triTable[cubeindex][i]];
		const auto& v1 = vertlist[triTable[cubeindex][i + 1]];
		const auto& v2 = vertlist[triTable[cubeindex][i + 2]];

		Triangle3d triangle({ v0,v1,v2 });
		triangles.push_back(triangle);

		ntriang++;
	}

	return(ntriang);
}

