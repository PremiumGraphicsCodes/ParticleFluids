#pragma once

#include "Voxel.h"

namespace Crystal {
	namespace Space {

class VoxelFiller
{
public:
	Util::Array3d<bool> fill(Voxel& voxel);

private:
	Util::Array3d<bool> scanX(const Voxel& voxel);

	Util::Array3d<bool> scanY(const Voxel& voxel);

	Util::Array3d<bool> scanZ(const Voxel& voxel);

	Util::Array3d<bool> scanAll(const std::array<Util::Array3d<bool>,3>& voxels);

};
	}
}