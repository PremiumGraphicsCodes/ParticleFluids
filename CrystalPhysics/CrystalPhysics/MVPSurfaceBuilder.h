#pragma once

#include <vector>
#include "Crystal/Math/Vector3d.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPMassParticle.h"
#include "CrystalSpace/CrystalSpace/MCCell.h"
#include "CrystalSpace/CrystalSpace/MarchingCubesAlgo.h"

namespace Crystal {
	namespace Physics {

class MVPSurfaceBuilder
{
public:

	void build(const Space::CompactSpaceHash3d& hash, const double threshold);

	//float getVolumeAt(const Math::Vector3df& pos);

	std::vector<Math::Triangle3d> getTriangles() const { return mc.getTriangles(); }

private:
	Space::MarchingCubesAlgo mc;
	//std::vector<Space::MCCell> mcCells;

};
	}
}