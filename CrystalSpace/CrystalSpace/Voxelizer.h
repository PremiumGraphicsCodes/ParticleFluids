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
	void voxelize(const Shape::PolygonMesh& polygon, const float res);

	void voxelize(const Shape::PolygonMesh& polygon, const std::array<int,3>& res);

	std::vector<Math::Vector3dd> getPoints() const { return points; }

private:
	std::vector<Math::Vector3dd> points;
};
	}
}