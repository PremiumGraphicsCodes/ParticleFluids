#pragma once

#include "../../Crystal/Shape/PolygonMesh.h"
#include "Voxel.h"

namespace Crystal {
	namespace Space {

class MeshToVoxelConverter
{
public:
	void convert(const Shape::PolygonMesh& mesh, const double divideLength);

	void subdivide(const Math::Triangle3d& triangle, const double divideLength);

private:
	Voxel voxel;

	std::vector<Math::Vector3dd> positions;
};
	}
}