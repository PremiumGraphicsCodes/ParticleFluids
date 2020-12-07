#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VolumeToMeshConverter
{
public:
	std::unique_ptr<VDBPolygonMesh> toMesh(const VDBVolume& volume);

private:
};

	}
}