#pragma once

#include <vector>
#include "../../Crystal/Math/Vector3d.h"

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

private:
};
	}
}