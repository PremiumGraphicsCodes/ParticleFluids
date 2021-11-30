#include "MVPSurfaceBuilder.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSurfaceBuilder::build(const size_t tableSize, const float searchRadius)
{
	//volume.createNode()
	hash.setup(searchRadius * 2.0, tableSize);
}

void MVPSurfaceBuilder::add(MVPMassParticle* massParticle)
{
	hash.add(massParticle);

	//hash.getTable()
}

void MVPSurfaceBuilder::buildVolume()
{
	auto cells = hash.getCells();
	for (auto c : cells) {
		c->
	}
}
