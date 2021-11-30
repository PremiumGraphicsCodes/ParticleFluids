#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "Voxel.h"

#include <vector>
#include <memory>

namespace Crystal {
	namespace Shape {
		class TriangleMesh;
	}
	namespace Space {

class ScanLineVoxelizer
{
public:
	void voxelize(const std::vector<Math::Triangle3d>& triangles, const Math::Box3dd& space, const double res);

	std::unique_ptr<Voxel> getVoxel() { return std::move(voxel); }

	std::vector<Math::Vector3dd> getIntersections() const { return intersections; }

private:
	std::unique_ptr<Voxel> voxel;
	std::vector<Math::Vector3dd> intersections;

};

	}
}