
#include "SPHSmoothSurfaceConstructor.h"

#include "../../Crystal/Shape/IParticle.h"
#include "../../CrystalSpace/CrystalAlgo/CompactSpaceHash3d.h"

#include "WPCA.h"

//using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Search;
using namespace Crystal::Physics;

void SPHSmoothSurfaceConstructor::add(IParticle* particle)
{
	this->particles.push_back(particle);
}

void SPHSmoothSurfaceConstructor::construct(const float searchRadius)
{
	CompactSpaceHash3d spaceHash(searchRadius, particles.size());
	for (auto p : particles) {
		spaceHash.add(p);
	}

	for (auto p : particles) {
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		WPCA wpca;
		wpca.calculate(p, neighbors, searchRadius);
	}
}
