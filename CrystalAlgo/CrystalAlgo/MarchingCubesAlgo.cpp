//from http://paulbourke.net/geometry/polygonise/

#include "../../Crystal/Math/Vector3d.h"
#include "MarchingCubesAlgo.h"
#include "MarchingCubesTable.h"
#include "Volume.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;
using namespace Crystal::Algo::MarchingCubesTable;

int MarchingCubesAlgo::build(const Volume& volume, const double isoLevel)
{
	const auto unum = volume.getUNum();
	const auto vnum = volume.getVNum();
	const auto wnum = volume.getWNum();
	for (int i = 0; i < unum-1; ++i) {
		for (int j = 0; j < vnum-1; ++j) {
			for (int k = 0; k < wnum-1; ++k) {
				MCCell cell;

				cell.position[0] = volume.getPosition(i, j, k);
				cell.value[0] = volume.getValue(i,j,k);

				cell.position[1] = volume.getPosition(i+1, j, k);
				cell.value[1] = volume.getValue(i+1, j, k);

				cell.position[2] = volume.getPosition(i+1, j+1, k);
				cell.value[2] = volume.getValue(i+1, j+1, k);

				cell.position[3] = volume.getPosition(i, j + 1, k);
				cell.value[3] = volume.getValue(i, j+1, k);

				cell.position[4] = volume.getPosition(i, j, k+1);
				cell.value[4] = volume.getValue(i, j, k+1);

				cell.position[5] = volume.getPosition(i + 1, j, k+1);
				cell.value[5] = volume.getValue(i + 1, j, k+1);

				cell.position[6] = volume.getPosition(i + 1, j + 1, k+1);
				cell.value[6] = volume.getValue(i + 1, j + 1, k+1);

				cell.position[7] = volume.getPosition(i, j + 1, k+1);
				cell.value[7] = volume.getValue(i, j + 1, k+1);

				march(cell, isoLevel);
			}
		}
	}
	return triangles.size();
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
	if (cell.value[0] < isolevel) cubeindex |= 1;
	if (cell.value[1] < isolevel) cubeindex |= 2;
	if (cell.value[2] < isolevel) cubeindex |= 4;
	if (cell.value[3] < isolevel) cubeindex |= 8;
	if (cell.value[4] < isolevel) cubeindex |= 16;
	if (cell.value[5] < isolevel) cubeindex |= 32;
	if (cell.value[6] < isolevel) cubeindex |= 64;
	if (cell.value[7] < isolevel) cubeindex |= 128;

	/* Cube is entirely in/out of the surface */
	if (edgeTable[cubeindex] == 0)
		return(0);

	/* Find the vertices where the surface intersects the cube */
	if (edgeTable[cubeindex] & 1)
		vertlist[0] =
		getInterpolatedPosition(isolevel, cell.position[0], cell.position[1], cell.value[0], cell.value[1]);
	if (edgeTable[cubeindex] & 2)
		vertlist[1] =
		getInterpolatedPosition(isolevel, cell.position[1], cell.position[2], cell.value[1], cell.value[2]);
	if (edgeTable[cubeindex] & 4)
		vertlist[2] =
		getInterpolatedPosition(isolevel, cell.position[2], cell.position[3], cell.value[2], cell.value[3]);
	if (edgeTable[cubeindex] & 8)
		vertlist[3] =
		getInterpolatedPosition(isolevel, cell.position[3], cell.position[0], cell.value[3], cell.value[0]);
	if (edgeTable[cubeindex] & 16)
		vertlist[4] =
		getInterpolatedPosition(isolevel, cell.position[4], cell.position[5], cell.value[4], cell.value[5]);
	if (edgeTable[cubeindex] & 32)
		vertlist[5] =
		getInterpolatedPosition(isolevel, cell.position[5], cell.position[6], cell.value[5], cell.value[6]);
	if (edgeTable[cubeindex] & 64)
		vertlist[6] =
		getInterpolatedPosition(isolevel, cell.position[6], cell.position[7], cell.value[6], cell.value[7]);
	if (edgeTable[cubeindex] & 128)
		vertlist[7] =
		getInterpolatedPosition(isolevel, cell.position[7], cell.position[4], cell.value[7], cell.value[4]);
	if (edgeTable[cubeindex] & 256)
		vertlist[8] =
		getInterpolatedPosition(isolevel, cell.position[0], cell.position[4], cell.value[0], cell.value[4]);
	if (edgeTable[cubeindex] & 512)
		vertlist[9] =
		getInterpolatedPosition(isolevel, cell.position[1], cell.position[5], cell.value[1], cell.value[5]);
	if (edgeTable[cubeindex] & 1024)
		vertlist[10] =
		getInterpolatedPosition(isolevel, cell.position[2], cell.position[6], cell.value[2], cell.value[6]);
	if (edgeTable[cubeindex] & 2048)
		vertlist[11] =
		getInterpolatedPosition(isolevel, cell.position[3], cell.position[7], cell.value[3], cell.value[7]);

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

Vector3dd MarchingCubesAlgo::getInterpolatedPosition(const double isolevel, const Vector3dd& p1, const Vector3dd& p2, const double valp1, const double valp2)
{
	if (::fabs(isolevel - valp1) < 0.00001)
		return(p1);
	if (::fabs(isolevel - valp2) < 0.00001)
		return(p2);
	if (::fabs(valp1 - valp2) < 0.00001)
		return(p1);
	const auto mu = (isolevel - valp1) / (valp2 - valp1);
	return p1 + mu * (p2 - p1);
}
