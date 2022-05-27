#pragma once

#include <vector>
#include <memory>

#include "Crystal/Shape/Volume.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "VDBParticleSystemScene.h"
#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {
		class VDBVolumeScene;

class SmoothVolumeConverter
{
public:
	std::vector<VDBVolumeScene*> build(VDBParticleSystemScene* vdbParticles, const float particleRadius, const float cellLength, const std::vector<std::string>& floatNames);

private:
};

	}
}