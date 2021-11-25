#include "MVPSurfaceBuilder.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSurfaceBuilder::build(const std::vector<Vector3df>& positions, const float searchRadius)
{
	ParticleSystem<float> particleSystem;
	for (const auto& p : positions) {
		particleSystem.add(p, 0.0);
	}

	CompactSpaceHash3d hash;
	hash.setup(searchRadius * 2.0, positions.size());

	const auto particles = particleSystem.getParticles();
	for (auto p : particles) {
		hash.add(p);
	}

	const auto cells = hash.getCells();
//	for (auto c : cells) {
//		c->
//		const auto index = hash.toIndex(p->getPosition());
//	}

//	hash.find()
	//hash.
}