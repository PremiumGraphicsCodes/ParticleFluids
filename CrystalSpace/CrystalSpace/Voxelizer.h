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
	std::vector<Math::Vector3dd> voxelizeToPoints(const Shape::PolygonMesh& polygon, const float res);

	std::vector<Math::Vector3dd> voxelizeToPoints(const Shape::PolygonMesh& polygon, const std::array<int,3>& res);

	std::unique_ptr<Voxel> voxelize(const Shape::PolygonMesh& polygon, const double res);

private:
};
	}
}