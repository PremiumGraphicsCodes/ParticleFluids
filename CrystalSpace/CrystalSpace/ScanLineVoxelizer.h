#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "Voxel.h"

#include <vector>
#include <memory>

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace Space {

class ScanLineVoxelizer
{
public:
	void voxelize(const Shape::PolygonMesh& polygon, const Math::Box3dd& space, const double res);

	std::unique_ptr<Voxel> getVoxel() { return std::move(voxel); }

private:
	std::unique_ptr<Voxel> voxel;

};

	}
}