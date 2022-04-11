#include "MVPVolumeConverter.h"

#include "Crystal/Math/Sphere3d.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/SparseVolumeBuilder.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "Crystal/Util/Array3d.h"
#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPVolumeConverter::build(const std::vector<MVPVolumeParticle*>& volumeParticles, const double cellLength)
{
	if (volumeParticles.empty()) {
		return;
	}

	const auto tableSize = static_cast<int>(volumeParticles.size());

	SparseVolumeBuilder builder;
	builder.build(Vector3df(cellLength), tableSize);
	for (auto vp : volumeParticles) {
		builder.add(Sphere3dd(vp->getPosition(), vp->getRadius()));
	}

	this->sparseVolume = std::move( builder.get() );

	CompactSpaceHash3d spaceHash(cellLength, volumeParticles.size());
	for (auto vp : volumeParticles) {
		spaceHash.add(vp);
	}

	//const auto cellRadius = cellLength * 0.5;

	const auto nodes = this->sparseVolume->getNodes();
	for (auto node : nodes) {
		const auto neighbors = spaceHash.findNeighbors(node->getPosition());
		const auto center = node->getPosition();
		for (auto n : neighbors) {
			auto vp = static_cast<MVPVolumeParticle*>(n);
			const auto masses = vp->getMassParticles();
			for (auto m : masses) {
				const auto d = Math::getDistanceSquared(m->getPosition(), center);
				if (d < cellLength * cellLength) {
					node->setValue(node->getValue() + m->getMass());
				}
				n->getPosition();
			}
		}
	}
}