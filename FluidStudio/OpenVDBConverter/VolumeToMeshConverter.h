#pragma once

#include "PolygonMesh.h"
#include "Volume.h"

namespace Crystal {
	namespace OpenVDB {

class VolumeToMeshConverter
{
public:
	std::unique_ptr<PolygonMesh> toMesh(const Volume& volume);

private:
};

	}
}