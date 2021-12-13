#pragma once

#include <vector>
#include "Crystal/Math/Vector3d.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPMassParticle.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPVolumeParticle.h"
#include "CrystalSpace/CrystalSpace/MCCell.h"
#include "CrystalSpace/CrystalSpace/MarchingCubesAlgo.h"

namespace Crystal {
	namespace Physics {

class MVPSurfaceBuilder
{
public:
	void build(const std::vector<MVPVolumeParticle*>& particles, const int res, const double threshold);

	void buildVolumes(const std::vector<Shape::IParticle*>& volumeParticles, const double radius, const int res);

	void buildMasses(const std::vector<Shape::IParticle*>& massParticles, const double radius);

	void buildCells(const double threshold);

	//float getVolumeAt(const Math::Vector3df& pos);

	std::vector<Math::Triangle3d> getTriangles() const { return mc.getTriangles(); }

private:
	std::unique_ptr<Space::SparseVolumef> sparseVolume;
	Space::MarchingCubesAlgo mc;
	std::vector<Space::MCCell> mcCells;

};
	}
}