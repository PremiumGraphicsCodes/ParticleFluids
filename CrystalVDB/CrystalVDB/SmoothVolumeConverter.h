#pragma once

#include <vector>
#include <memory>

#include "Crystal/Shape/Volume.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "VDBParticleSystemScene.h"
#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {

class SmoothVolumeConverter
{
public:
	//void add(Shape::IParticle* particle);

	void buildIsotoropic(VDBParticleSystemScene* vdbParticles, const float particleRadius, const float cellLength, VDBVolumeScene* vdbVolume, VDBVolumeScene* temperatureVolume);

	void build(VDBParticleSystemScene* vdbParticles, const float particleRadius, const float cellLength, VDBVolumeScene* vdbVolume, VDBVolumeScene* temperatureVolume);

private:
};

	}
}