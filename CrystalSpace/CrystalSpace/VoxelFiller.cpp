#include "VoxelFiller.h"

using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	enum VoxelType {
		INSIDE_X,
		INSIDE_Y,
		INSIDE_Z
	};

}

void VoxelFiller::fill(Voxel& voxel)
{


	const auto resolutions = voxel.getResolutions();

	// along x.
	for (int k = 0; k < resolutions[2]; ++k) {
		for (int j = 0; j < resolutions[1]; ++j) {
			bool isInside = false;
			for (int i = 0; i < resolutions[0]; ++i) {
				if (voxel.getValue(i, j, k)) {
					isInside = !isInside;
				}
			}
			if (isInside) {
				
			}
		}
	}
}


/* from https://github.com/sylefeb/VoxSurf/blob/master/main.cpp
// --------------------------------------------------------------

// This version is more robust by using all three direction
// and voting among them to decide what is filled or not
void fillInsideVoting(Array3D<uchar>& _voxs)
{
  // along x
  ForIndex(k, _voxs.zsize()) {
	ForIndex(j, _voxs.ysize()) {
	  bool inside = false;
	  ForIndex(i, _voxs.xsize()) {
		if (_voxs.at(i, j, k) & ALONG_X) {
		  inside = !inside;
		}
		if (inside) {
		  _voxs.at(i, j, k) |= INSIDE_X;
		}
	  }
	}
  }
  // along y
  ForIndex(k, _voxs.zsize()) {
	ForIndex(j, _voxs.xsize()) {
	  bool inside = false;
	  ForIndex(i, _voxs.ysize()) {
		if (_voxs.at(j, i, k) & ALONG_Y) {
		  inside = !inside;
		}
		if (inside) {
		  _voxs.at(j, i, k) |= INSIDE_Y;
		}
	  }
	}
  }
  // along z
  ForIndex(k, _voxs.ysize()) {
	ForIndex(j, _voxs.xsize()) {
	  bool inside = false;
	  ForIndex(i, _voxs.zsize()) {
		if (_voxs.at(j, k, i) & ALONG_Z) {
		  inside = !inside;
		}
		if (inside) {
		  _voxs.at(j, k, i) |= INSIDE_Z;
		}
	  }
	}
  }
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
}

// --------------------------------------------------------------

void fillInside(Array3D<uchar>& _voxs)
{
  ForIndex(k, _voxs.zsize()) {
	ForIndex(j, _voxs.ysize()) {
	  bool inside = false;
	  ForIndex(i, _voxs.xsize()) {
		if (_voxs.at(i, j, k) & ALONG_X) {
		  inside = !inside;
		}
		if (inside) {
		  _voxs.at(i, j, k) |= INSIDE;
		}
	  }
	}
  }
}*/