#pragma once

#include "Voxel.h"

namespace Crystal {
	namespace Space {

class VoxelFiller
{
public:
	void fill(Voxel& voxel);

	void scanX(const Voxel& voxel, Util::Array3d<unsigned char>& array3d);

	void scanY(const Voxel& voxel, Util::Array3d<unsigned char>& array3d);

	void scanZ(const Voxel& voxel, Util::Array3d<unsigned char>& array3d);

	void vote(Util::Array3d<unsigned char>& array3d);

private:
};
	}
}