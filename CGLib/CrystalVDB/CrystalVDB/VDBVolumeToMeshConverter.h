#pragma once

#include "VDBPolygonMeshScene.h"
#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeToMeshConverter
{
public:
	static VDBPolygonMeshScene* toMesh(const VDBVolumeScene& volume, const double threshold, const double adaptivity);
};
	}
}