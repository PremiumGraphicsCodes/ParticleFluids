#include "VoxelFiller.h"

using namespace Crystal::Util;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	constexpr unsigned char INSIDE_X = 0x01;
	constexpr unsigned char INSIDE_Y = 0x02;
	constexpr unsigned char INSIDE_Z = 0x04;
}

// reference https://github.com/sylefeb/VoxSurf/blob/master/main.cpp

void VoxelFiller::fill(Voxel& voxel)
{
	const auto resolutions = voxel.getResolutions();

	Array3d<unsigned char> array3d(resolutions);

	scanX(voxel,array3d);
}

// along x.
void VoxelFiller::scanX(const Voxel& voxel, Array3d<unsigned char> & array3d)
{
	const auto& resolutions = array3d.getResolutions();

	for (int k = 0; k < resolutions[2]; ++k) {
		for (int j = 0; j < resolutions[1]; ++j) {
			bool isInside = false;
			for (int i = 0; i < resolutions[0]; ++i) {
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
				if (isInside) {
					auto flag = array3d.get(i, j, k);
					flag |= ::INSIDE_X;
					array3d.set(i, j, k, flag);
				}
			}
		}
	}
}

// along y
void VoxelFiller::scanY(const Voxel& voxel, Array3d<unsigned char>& array3d)
{
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
					auto flag = array3d.get(i, j, k);
					flag |= ::INSIDE_Y;
					array3d.set(i, j, k, flag);
				}
			}
		}
	}
}

// along z
void VoxelFiller::scanZ(const Voxel & voxel, Array3d<unsigned char> & array3d)
{
	const auto& resolutions = array3d.getResolutions();

	for (int j = 0; j < resolutions[1]; ++j) {
		for (int i = 0; i < resolutions[0]; ++i) {
			bool isInside = false;
			for (int k = 0; k < resolutions[2]; ++k) {
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
				if (isInside) {
					auto flag = array3d.get(i, j, k);
					flag |= ::INSIDE_Z;
					array3d.set(i, j, k, flag);
				}
			}
		}
	}
}

void VoxelFiller::vote(Array3d<unsigned char>& array3d)
{
	/*
  // voting
  ForArray3D(_voxs, i, j, k) {
	uchar v = _voxs.at(i, j, k);
	int votes =
	  (  (v & INSIDE_X) ? 1 : 0)
	  + ((v & INSIDE_Y) ? 1 : 0)
	  + ((v & INSIDE_Z) ? 1 : 0);
	// clean
	_voxs.at(i, j, k) &= ~(INSIDE_X | INSIDE_Y | INSIDE_Z);
	if (votes > 1) {
	  // tag as inside
	  _voxs.at(i, j, k) |= INSIDE;
	}
  }
  */
}