#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VolumeToMeshConverter
{
public:
	VDBPolygonMesh* toMesh(const VDBVolume& volume);

private:
};

	}
}