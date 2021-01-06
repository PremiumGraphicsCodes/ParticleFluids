#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {
		class VDBParticleSystem;

class VDBVolumeConverter
{
public:
	void toMesh(const VDBVolumeScene& volume, VDBPolygonMesh* mesh);

	void toParticleSystem(const VDBVolumeScene& volume, VDBParticleSystem* ps) const;

private:
};

	}
}