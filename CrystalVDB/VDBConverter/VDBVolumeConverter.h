#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeConverter
{
public:
	void toMesh(const VDBVolume& volume, VDBPolygonMesh* mesh);

private:
};

	}
}