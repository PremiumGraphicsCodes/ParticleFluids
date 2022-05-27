
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

	temperatureVolume->setScale(cellLength);
	auto accessor2 = temperatureVolume->getImpl()->getPtr()->getAccessor();

	const auto r = static_cast<int>( particleRadius / cellLength ) / 2;
	


	auto psGrid = vdbParticles->getImpl()->getPtr();
	for (auto leafIter = psGrid->tree().cbeginLeaf(); leafIter; ++leafIter) {
		const auto& array = leafIter->constAttributeArray("P");
		const auto& array2 = leafIter->constAttributeArray("temperature");

		openvdb::points::AttributeHandle<openvdb::Vec3f> positionHandle(array);
		openvdb::points::AttributeHandle<float> floatHandle(array2);
		for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
			openvdb::Vec3f voxelPosition = positionHandle.get(*indexIter);
			const auto xyz = indexIter.getCoord().asVec3d();
			openvdb::Vec3f worldPosition = psGrid->transform().indexToWorld(voxelPosition + xyz);
			auto ix = *indexIter;
			const auto t = floatHandle.get(ix);

			const auto index = grid->worldToIndex(worldPosition);
			const auto p = worldPosition;

			for (int i = -r; i <= r; ++i) {
				for (int j = -r; j <= r; ++j) {
					for (int k = -r; k <= r; ++k) {
						const auto ix = index[0] + i;
						const auto iy = index[1] + j;
						const auto iz = index[2] + k;
						const auto c = openvdb::math::Coord(ix, iy, iz);
						const auto pos = grid->indexToWorld(c);
						const auto dist = std::pow(pos[0] - p[0], 2) + std::pow(pos[1] - p[1], 2) + std::pow(pos[2] - p[2], 2);
						const auto v = ::getCubicSpline(std::sqrt(dist), particleRadius);
						const auto vv = accessor.getValue(c) + v;
						accessor.setValue(c, vv);
						const auto tt = t * ::getCubicSpline(std::sqrt(dist), particleRadius);
						accessor2.setValue(c, tt + accessor2.getValue(c));
					}
				}
			}
		}
	}

	for (auto iter = grid->cbeginValueOn(); iter.test(); ++iter) {
		const auto value = *iter;
		const auto c = iter.getCoord();
		const auto t = accessor2.getValue(c);
		accessor2.setValue(c, t / value);
	}
}

std::vector<VDBVolumeScene*> SmoothVolumeConverter::build(VDBParticleSystemScene* vdbParticles, const float particleRadius, const float cellLength, const std::vector<std::string>& floatNames)
{
	std::vector<VDBVolumeScene*> vdbVolumes;

	auto vdbVolume = new VDBVolumeScene();
	vdbVolume->getImpl()->getPtr()->setName("density");
	vdbVolume->setScale(cellLength);
	auto grid = vdbVolume->getImpl()->getPtr();
	auto accessor = grid->getAccessor();

	std::vector<openvdb::FloatGrid::Accessor> floatAccessors;
	for (const auto& n : floatNames) {
		auto vdbVolume = new VDBVolumeScene();
		vdbVolume->getImpl()->getPtr()->setName(n);
		vdbVolume->setScale(cellLength);
		auto grid = vdbVolume->getImpl()->getPtr();
		vdbVolumes.push_back(vdbVolume);
		floatAccessors.push_back(grid->getAccessor());
	}

	vdbVolumes.push_back(vdbVolume);

	const auto r = static_cast<int>(particleRadius / cellLength) / 2;

	const auto names = vdbParticles->getImpl()->getAttributeNames();

	auto psGrid = vdbParticles->getImpl()->getPtr();
	for (auto leafIter = psGrid->tree().cbeginLeaf(); leafIter; ++leafIter) {
		const auto& array = leafIter->constAttributeArray("P");
		std::vector<openvdb::points::AttributeHandle<float>> floatHandles;
		for (const auto& n : floatNames) {
			const auto& fa = leafIter->constAttributeArray("n");
			floatHandles.push_back(fa);
		}

		openvdb::points::AttributeHandle<openvdb::Vec3f> positionHandle(array);
		for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
			openvdb::Vec3f voxelPosition = positionHandle.get(*indexIter);
			const auto xyz = indexIter.getCoord().asVec3d();
			openvdb::Vec3f worldPosition = psGrid->transform().indexToWorld(voxelPosition + xyz);
			auto ix = *indexIter;
			std::vector<float> floatValues;
			for (const auto& fh : floatHandles) {
				floatValues.push_back(fh.get(ix));
			}

			const auto index = grid->worldToIndex(worldPosition);
			const auto p = worldPosition;

			for (int i = -r; i <= r; ++i) {
				for (int j = -r; j <= r; ++j) {
					for (int k = -r; k <= r; ++k) {
						const auto ix = index[0] + i;
						const auto iy = index[1] + j;
						const auto iz = index[2] + k;
						const auto c = openvdb::math::Coord(ix, iy, iz);
						const auto pos = grid->indexToWorld(c);
						const auto dist = std::pow(pos[0] - p[0], 2) + std::pow(pos[1] - p[1], 2) + std::pow(pos[2] - p[2], 2);
						const auto v = ::getCubicSpline(std::sqrt(dist), particleRadius);
						const auto vv = accessor.getValue(c) + v;
						accessor.setValue(c, vv);
						for (size_t i = 0; i < floatValues.size(); ++i) {
							const auto tt = floatValues[i] * ::getCubicSpline(std::sqrt(dist), particleRadius);
							floatAccessors[i].setValue(c, tt + floatAccessors[i].getValue(c));
						}
					}
				}
			}
		}
	}

	for (auto iter = grid->cbeginValueOn(); iter.test(); ++iter) {
		const auto value = *iter;
		const auto c = iter.getCoord();
		for (auto& fa : floatAccessors) {
			const auto t = fa.getValue(c);
			fa.setValue(c, t / value);
		}
	}
	return vdbVolumes;
}
