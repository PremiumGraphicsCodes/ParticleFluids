#pragma once

#include "../../Crystal/Shape/PolygonMesh.h"
#include "Voxel.h"

#include <memory>

namespace Crystal {
	namespace Space {

class MeshToVoxelConverter
{
public:
	void convert(const Shape::PolygonMesh& mesh, const double divideLength);

	void subdivide(const Math::Triangle3d& triangle, const double divideLength);

	void toVoxel(const double divideLength);

	std::unique_ptr<Voxel> toVoxel() { return std::move(voxel); }

private:
	std::unique_ptr<Voxel> voxel;

	std::vector<Math::Vector3dd> positions;
};
	}
}