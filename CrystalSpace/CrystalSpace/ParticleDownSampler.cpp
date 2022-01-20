#include "ParticleDownSampler.h"

#include "Crystal/Shape/IParticle.h"
#include "CompactSpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

std::vector<Vector3dd> ParticleDownSampler::downSample(const std::vector<IParticle*>& particles, const float leafSize)
{
	CompactSpaceHash3d spaceHash(leafSize, particles.size());
	for (auto p : particles) {
		spaceHash.add(p);
	}
	const auto cells = spaceHash.getCells();

	std::vector<Vector3dd> centers;
	for (auto c : cells) {
		Vector3dd center(0, 0, 0);
		for (auto p : c->particles) {
			center += p->getPosition();
		}
		center /= static_cast<float>( c->particles.size() );
		centers.push_back(center);
	}
	return centers;
}