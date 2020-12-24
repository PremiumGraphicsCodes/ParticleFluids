#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class MeshToVolumeConverter
{
public:
	std::unique_ptr<VDBVolume> toVolume(const VDBPolygonMesh& mesh);

private:
};

	}
}