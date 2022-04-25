
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
		SmoothParticle(const Vector3dd& p, const float radius, const float temperature) :
			position(p),
			density(0.0f),
			radius(radius),
			temperature(temperature)
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

		float getTemperature() const { return temperature; }

		void setTemperature(const float t) { this->temperature = t; }

	private:
		Vector3df position;
		float density;
		float radius;
		float temperature;
	};

}

void SmoothVolumeConverter::buildIsotoropic(VDBParticleSystemScene* vdbParticles, const float particleRadius, const float cellLength, VDBVolumeScene* vdbVolume, VDBVolumeScene* vdbTemperatureVolume)
{
	const auto positions = vdbParticles->getPositions();
	//vdbParticles->get

	const auto searchRadius = particleRadius;
	if (positions.empty()) {
		return;
	}

	std::vector<std::unique_ptr<SmoothParticle>> particles;
	for (const auto& p : positions) {
		particles.push_back(std::make_unique<SmoothParticle>(p, particleRadius, 300.0f));
	}

	if (vdbParticles->hasAttribute("temperature")) {
		const auto temperatures = vdbParticles->getFloatAttribute("temperature");
		for (int i = 0; i < temperatures.size(); ++i) {
			particles[i]->setTemperature(temperatures[i]);
		}
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

	{
		SparseVolumeBuilder builder;
		builder.build(Vector3df(cellLength), positions.size());
		for (auto& p : particles) {
			builder.add(Sphere3dd(p->getPosition(), particleRadius));
		}
		auto volume = builder.get();
		const auto nodes = volume->getNodes();

		SparseVolume<float> temperatureVolume(Vector3df(cellLength), positions.size());
		for (auto n : nodes) {
			temperatureVolume.createNode(n->getIndex());
		}
		auto tnodes = temperatureVolume.getNodes();

		CompactSpaceHash3d spaceHash(particleRadius, (int)particles.size());
		for (const auto& p : particles) {
			spaceHash.add(p.get());
		}

		std::vector<SparseVolumeNode<float>*> tns(tnodes.begin(), tnodes.end());
		std::vector<SparseVolumeNode<float>*> ns(nodes.begin(), nodes.end());
#pragma omp parallel for
		for (int i = 0; i < ns.size(); ++i) {
			auto node = ns[i];
			auto tnode = tns[i];
			const auto nodePos = node->getPosition();
			const auto neighbors = spaceHash.findNeighbors(node->getPosition());
			float totalWeight = 0.0;
			for (auto n : neighbors) {
				auto sp = static_cast<SmoothParticle*>(n);
				const auto v = n->getPosition() - nodePos;
				const auto d = glm::distance(n->getPosition(), nodePos);
				//const auto coe = 1400.0f / searchRadius / searchRadius / searchRadius;
				const auto w = ::getCubicSpline(d, sp->getRadius());
				const auto value = w * sp->getMass() / sp->getDensity();
				node->setValue(value + node->getValue());
				const auto t = w * sp->getTemperature();
				tnode->setValue(tnode->getValue() + t);
				totalWeight += w;
			}
			node->setValue(node->getValue() / totalWeight);
			tnode->setValue(tnode->getValue() / totalWeight);
		}

		VDBVolumeConverter converter;
		converter.fromSparseVolume(*volume, vdbVolume);
		converter.fromSparseVolume(temperatureVolume, vdbTemperatureVolume);
	}
}

#include "VDBVolumeImpl.h"
#include "VDBParticleSystemImpl.h"

void SmoothVolumeConverter::build(VDBParticleSystemScene* vdbParticles, const float particleRadius, const float cellLength, VDBVolumeScene* vdbVolume, VDBVolumeScene* temperatureVolume)
{
	//VDBVolumeImpl volume;
	vdbVolume->setScale(cellLength);
	auto grid = vdbVolume->getImpl()->getPtr();
	auto accessor = grid->getAccessor();
	//const auto cellLength = grid->voxelSize();
	
	const auto positions = vdbParticles->getImpl()->getPositions();
	for (auto p : positions) {
		const auto index = grid->worldToIndex(p);
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				for (int k = -1; k <= 1; ++k) {
					const auto ix = index[0] + i;
					const auto iy = index[1] + j;
					const auto iz = index[2] + k;
					const auto c = openvdb::math::Coord(ix, iy, iz);
					const auto pos = grid->indexToWorld(c);
					const auto dist = std::pow(pos[0] - p[0], 2) + std::pow(pos[1] - p[1], 2) + std::pow(pos[2] - p[2], 2);
					const auto v = ::getCubicSpline(std::sqrt(dist), particleRadius);
					const auto vv = accessor.getValue(c) + v;
					accessor.setValue(c, vv);
				}
			}
		}
	}
}