#include "ParticleDownSampler.h"

#include "Crystal/Shape/IParticle.h"
#include "CompactSpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

Box3dd ParticleDownSampler::calculateBox(const std::vector<IParticle*>& particles, const float cellLength)
{
	Box3dd b = Box3dd::createDegeneratedBox();
	for (auto p : particles) {
		b.add(p->getPosition());
	}
	const auto maxLength = std::max(std::max(b.getLength().x, b.getLength().y), b.getLength().z);
	const auto l = maxLength / cellLength;
	const auto level = std::max(3.0, std::floor(std::log2(l) + 1.0));
	const auto ll = std::pow(2, level);
	const auto minIndex = (b.getMin() / (double)cellLength);
	const auto ix = std::floor(minIndex[0]) * cellLength;
	const auto iy = std::floor(minIndex[1]) * cellLength;
	const auto iz = std::floor(minIndex[2]) * cellLength;
	const Vector3dd v1(ix, iy, iz);
	return Box3dd(v1, v1 + ll * cellLength);
}

std::vector<Vector3df> ParticleDownSampler::downSample(const std::vector<IParticle*>& particles, const float leafSize, const Box3df& bb)
{
	CompactSpaceHash3d spaceHash(leafSize, particles.size());
	for (auto p : particles) {
		spaceHash.add(p);
	}
	const auto cells = spaceHash.getCells();

	std::vector<Vector3df> centers;
	for (auto c : cells) {
		Vector3df center(0, 0, 0);
		for (auto p : c->particles) {
			center += p->getPosition();
		}
		center /= static_cast<float>( c->particles.size() );
		centers.push_back(center);
	}
	return centers;
}