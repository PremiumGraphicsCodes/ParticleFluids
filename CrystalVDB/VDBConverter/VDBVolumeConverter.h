#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {
		class VDBParticleSystem;

class VDBVolumeConverter
{
public:
	void toMesh(const VDBVolume& volume, VDBPolygonMesh* mesh);

	void toParticleSystem(const VDBVolume& volume, VDBParticleSystem* ps) const;

private:
};

	}
}