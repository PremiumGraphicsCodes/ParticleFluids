#pragma once

#include <vector>
#include <list>
#include <memory>

#include "../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;

class MVPBoundarySolver
{
public:
	MVPBoundarySolver() {}

	void addBoundaryScene(MVPFluidScene* scene) { this->boundaries.push_back(scene); }

	void setup(const float effectLength);

	void clear() {
		boundaries.clear();
		//		spaceHash.clear();
	}

	std::vector<Shape::IParticle*> findNeighbors(const Math::Vector3dd& position);

private:
	std::list<MVPFluidScene*> boundaries;
	std::unique_ptr<Space::CompactSpaceHash3d> spaceHash;
};

	}
}