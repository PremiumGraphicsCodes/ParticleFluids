#pragma once

#include <vector>
#include <list>
#include <memory>

#include "../../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;
		class CSGBoundaryScene;
		class MVPVolumeParticle;

class MVPBoundarySolver
{
public:
	MVPBoundarySolver() {}

	void addBoundaryScene(MVPFluidScene* scene) { this->boundaries.push_back(scene); }

	void setup(const float effectLength);

	void clear() {
		boundaries.clear();
		csgBoundaries.clear();
		//		spaceHash.clear();
	}

	std::vector<Shape::IParticle*> findNeighbors(const Math::Vector3dd& position);

	void add(CSGBoundaryScene* csg) { this->csgBoundaries.push_back(csg); }

	void solvePressure(MVPVolumeParticle* particle, const double dt);

private:
	std::list<MVPFluidScene*> boundaries;
	std::unique_ptr<Space::CompactSpaceHash3d> spaceHash;
	std::list<CSGBoundaryScene*> csgBoundaries;
};

	}
}