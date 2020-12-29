#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VolumeToMeshConverter
{
public:
	void toMesh(const VDBVolume& volume, VDBPolygonMesh* mesh);

private:
};

	}
}