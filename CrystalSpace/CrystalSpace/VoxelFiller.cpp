#include "VoxelFiller.h"

using namespace Crystal::Util;
using namespace Crystal::Shape;
using namespace Crystal::Space;

// reference https://github.com/sylefeb/VoxSurf/blob/master/main.cpp

Array3d<bool> VoxelFiller::fill(Voxel& voxel)
{
	const auto resolutions = voxel.getResolutions();

	Array3d<unsigned char> array3d(resolutions);

	const auto voxelX = scanX(voxel);
	const auto voxelY = scanY(voxel);
	const auto voxelZ = scanZ(voxel);

	return scanAll({ voxelX, voxelY, voxelZ });
}

// along x.
Array3d<bool> VoxelFiller::scanX(const Voxel& voxel)
{
	Array3d<bool> array3d(voxel.getResolutions());
	const auto& resolutions = array3d.getResolutions();

	for (int k = 0; k < resolutions[2]; ++k) {
		for (int j = 0; j < resolutions[1]; ++j) {
			bool isInside = false;
			for (int i = 0; i < resolutions[0]; ++i) {
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
				if (isInside) {
					auto flag = array3d.get(i, j, k) | isInside;
					array3d.set(i, j, k, flag);
				}
			}
		}
	}
	return array3d;
}

// along y
Array3d<bool> VoxelFiller::scanY(const Voxel& voxel)
{
	Array3d<bool> array3d(voxel.getResolutions());
	const auto& resolutions = array3d.getResolutions();

	for (int k = 0; k < resolutions[2]; ++k) {
		for (int i = 0; i < resolutions[0]; ++i) {
			bool isInside = false;
			for (int j = 0; j < resolutions[1]; ++j) {
				bool isInside = false;
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
				if (isInside) {
					auto flag = array3d.get(i, j, k) | isInside;
					array3d.set(i, j, k, flag);
				}
			}
		}
	}
	return array3d;
}

// along z
Array3d<bool> VoxelFiller::scanZ(const Voxel& voxel)
{
	Array3d<bool> array3d(voxel.getResolutions());
	const auto& resolutions = array3d.getResolutions();

	for (int j = 0; j < resolutions[1]; ++j) {
		for (int i = 0; i < resolutions[0]; ++i) {
			bool isInside = false;
			for (int k = 0; k < resolutions[2]; ++k) {
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
				if (isInside) {
					auto flag = array3d.get(i, j, k) | isInside;
					array3d.set(i, j, k, flag);
				}
			}
		}
	}
	return array3d;
}

Array3d<bool> VoxelFiller::scanAll(const std::array<Util::Array3d<bool>, 3>& voxels)
{
	Array3d<bool> array3d(voxels[0].getResolutions());
	const auto& resolutions = voxels[0].getResolutions();

	for (int x = 0; x < resolutions[0]; ++x) {
		for (int y = 0; y < resolutions[1]; ++y) {
			for (int z = 0; z < resolutions[2]; ++z) {
				const auto v = array3d.get(x, y, z);
				const auto xIsInside = voxels[0].get(x, y, z);
				const auto yIsInside = voxels[1].get(x, y, z);
				const auto zIsInside = voxels[2].get(x, y, z);
				if (xIsInside || yIsInside || zIsInside) {
					array3d.set(x, y, z, true);
				}
			}
		}
	}
	return array3d;
}