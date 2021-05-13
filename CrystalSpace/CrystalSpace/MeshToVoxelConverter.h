#pragma once

#include "../../Crystal/Shape/PolygonMesh.h"
#include "Voxel.h"

namespace Crystal {
	namespace Space {

class MeshToVoxelConverter
{
public:
	void convert(const Shape::PolygonMesh& mesh, const double divideLength);

private:
	Voxel voxel;
};
	}
}