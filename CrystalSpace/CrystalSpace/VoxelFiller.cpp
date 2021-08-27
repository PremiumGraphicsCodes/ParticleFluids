#include "VoxelFiller.h"

using namespace Crystal::Util;
using namespace Crystal::Shape;
using namespace Crystal::Space;

// reference https://github.com/sylefeb/VoxSurf/blob/master/main.cpp

Array3d<bool> VoxelFiller::fill(Voxel& voxel)
{
	const auto resolutions = voxel.getResolutions();

	const auto voxelX = scanX(voxel);
	const auto voxelY = scanY(voxel);
	const auto voxelZ = scanZ(voxel);

	return scanAll({ voxelX, voxelY, voxelZ });
}

// along x.
Array3d<bool> VoxelFiller::scanX(const Voxel& voxel)
{
	Array3d<bool> array3d(voxel.getResolutions(), false);
	const auto& resolutions = array3d.getResolutions();

	for (int k = 0; k < resolutions[2]; ++k) {
		for (int j = 0; j < resolutions[1]; ++j) {
			bool isInside = false;
			for (int i = 0; i < resolutions[0]; ++i) {
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
				array3d.set(i, j, k, isInside);
			}
		}
	}
	return array3d;
}

// along y
Array3d<bool> VoxelFiller::scanY(const Voxel& voxel)
{
	Array3d<bool> array3d(voxel.getResolutions(), false);
	const auto& resolutions = array3d.getResolutions();

	for (int k = 0; k < resolutions[2]; ++k) {
		for (int i = 0; i < resolutions[0]; ++i) {
			bool isInside = false;
			for (int j = 0; j < resolutions[1]; ++j) {
				bool isInside = false;
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
				array3d.set(i, j, k, isInside);
			}
		}
	}
	return array3d;
}

// along z
Array3d<bool> VoxelFiller::scanZ(const Voxel& voxel)
{
	Array3d<bool> array3d(voxel.getResolutions(), false);
	const auto& resolutions = array3d.getResolutions();

	for (int j = 0; j < resolutions[1]; ++j) {
		for (int i = 0; i < resolutions[0]; ++i) {
			bool isInside = false;
			for (int k = 0; k < resolutions[2]; ++k) {
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
				array3d.set(i, j, k, isInside);
			}
		}
	}
	return array3d;
}

Array3d<bool> VoxelFiller::scanAll(const std::array<Util::Array3d<bool>, 3>& voxels)
{
	Array3d<bool> array3d(voxels[0].getResolutions(), false);
	const auto& resolutions = voxels[0].getResolutions();

	for (int i = 0; i < resolutions[0]; ++i) {
		for (int j = 0; j < resolutions[1]; ++j) {
			for (int k = 0; k < resolutions[2]; ++k) {
				const auto v = array3d.get(i, j, k);
				const auto xIsInside = voxels[0].get(i, j, k);
				const auto yIsInside = voxels[1].get(i, j, k);
				const auto zIsInside = voxels[2].get(i, j, k);
				if (xIsInside || yIsInside || zIsInside) {
					array3d.set(i, j, k, true);
				}
			}
		}
	}
	return array3d;
}