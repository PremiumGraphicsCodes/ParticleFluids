
#include "SmoothVolumeConverter.h"

#include "Crystal/Shape/IParticle.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalSpace/CrystalSpace/SparseVolumeBuilder.h"
#include "CrystalSpace/CrystalSpace/DynamicOctree.h"

#include "Crystal/Math/Sphere3d.h"
#include "VDBVolumeConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::VDB;

namespace {
	float getCubicSpline(const float distance, const float effectLength)
	{
		const auto q = distance * 2 / (effectLength);

		if (q < 1) {
			return (2.0f / 3.0f - q * q + 0.5f * q * q * q);
		}
		else if (q < 2) {
			return (std::pow(2.0f - q, 3.0f) / 6.0f);
		}
		else {
			return 0;
		}
	}

	class SmoothParticle : public IParticle
	{
	public:
		SmoothParticle(const Vector3dd& p, const float radius) :
			position(p),
			density(0.0f),
			radius(radius)
		{}

		Vector3dd getPosition() const override { return position; }

		void calculateDensity(const std::vector<IParticle*>& neighbors, const float searchRadius) {
			const auto mass = getMass();
			for (auto n : neighbors) {
				const auto distanceSquared = ::getDistanceSquared((Vector3df)(n->getPosition()), this->position);
				this->density += mass * ::getCubicSpline(::sqrt(distanceSquared), radius);
			}
		}

		float getDensity() const { return density; }

		float getMass() const {
			const auto diameter = radius * 2.0;
			return diameter * diameter * diameter;
		}

		float getRadius() const { return radius; }

	private:
		Vector3df position;
		float density;
		float radius;
	};

}

void SmoothVolumeConverter::buildIsotoropic(VDBParticleSystemScene* vdbParticles, const float particleRadius, const float cellLength, VDBVolumeScene* vdbVolume)
{
	const auto positions = vdbParticles->getPositions();

	const auto searchRadius = particleRadius;
	if (positions.empty()) {
		return;
	}

	std::vector<std::unique_ptr<SmoothParticle>> particles;
	for (const auto& p : positions) {
		particles.push_back(std::make_unique<SmoothParticle>(p, particleRadius));
	}

	CompactSpaceHash3d spaceHash1(searchRadius, particles.size());

	for (const auto& p : particles) {
		spaceHash1.add(p.get());
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto& p = particles[i];
		const auto neighbors = spaceHash1.findNeighbors(p->getPosition());
		p->calculateDensity(neighbors, searchRadius);
	}
	//calculateDensity(particleRadius);

	SparseVolumeBuilder builder;
	builder.build(Vector3df(cellLength), positions.size());
	for (auto& p : particles) {
		builder.add(Sphere3dd(p->getPosition(), particleRadius));
	}
	auto volume = builder.get();
	const auto nodes = volume->getNodes();

	CompactSpaceHash3d spaceHash(particleRadius, (int)particles.size());
	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

	std::vector<SparseVolumeNode<float>*> ns(nodes.begin(), nodes.end());
#pragma omp parallel for
	for (int i = 0; i < ns.size(); ++i) {
		auto node = ns[i];
		const auto nodePos = node->getPosition();
		const auto neighbors = spaceHash.findNeighbors(node->getPosition());
		for (auto n : neighbors) {
			auto sp = static_cast<SmoothParticle*>(n);
			const auto v = n->getPosition() - nodePos;
			const auto d = glm::distance(n->getPosition(), nodePos);
			//const auto coe = 1400.0f / searchRadius / searchRadius / searchRadius;
			const auto w = ::getCubicSpline(d, sp->getRadius()) * sp->getMass() / sp->getDensity();
			const auto value = node->getValue();
			node->setValue(w + value);
		}
	}
	VDBVolumeConverter converter;
	converter.fromSparseVolume(*volume, vdbVolume);
}