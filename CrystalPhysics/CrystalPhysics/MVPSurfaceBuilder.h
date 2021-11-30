#pragma once

#include <vector>
#include "Crystal/Math/Vector3d.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPMassParticle.h"

namespace Crystal {
	namespace Physics {

class MVPSurfaceBuilder
{
public:
	void build(const size_t tableSize, const float searchRadius);

	void add(MVPMassParticle* massParticle);

	void buildVolume();

	//float getVolumeAt(const Math::Vector3df& pos);

private:
	//Space::SparseVolumef volume;
	Space::CompactSpaceHash3d hash;

};
	}
}