#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {
		class VDBParticleSystemScene;

class VDBVolumeConverter
{
public:
	void toMesh(const VDBVolumeScene& volume, VDBPolygonMesh* mesh);

	void toParticleSystem(const VDBVolumeScene& volume, VDBParticleSystemScene* ps) const;

private:
};

	}
}