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

class Voxelizer
{
public:
	std::unique_ptr<Voxel> voxelize(const Shape::PolygonMesh& polygon, const double res);

private:
};
	}
}