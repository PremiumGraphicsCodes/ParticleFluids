
#include "SPHSurfaceBuilder.h"

#include "Crystal/Shape/IParticle.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalSpace/CrystalSpace/SparseVolumeBuilder.h"

//#include <set>
//#include <map>

#include "WPCA.h"
#include "../SPHKernel.h"

#include "Crystal/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

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
}

void SPHSurfaceBuilder::buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength)
{
	const auto searchRadius = particleRadius; //* 8.0;
	//const auto cellLength = searchRadius * 0.5;

	for (auto p : positions) {
		particles.push_back(std::make_unique<SPHSurfaceParticle>(p, particleRadius));
	}

	CompactSpaceHash3d spaceHash(searchRadius, (int)particles.size());
	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

	const SPHKernel kernel(searchRadius);
	for (const auto& p : particles) {
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		p->calculateDensity(neighbors, searchRadius, kernel);
	}

	SparseVolumeBuilder builder;
	builder.build(Vector3df(cellLength, cellLength, cellLength), particles.size());
	//this->volume = createSparseVolume(positions, cellLength);

	for (const auto& p : particles) {
		const auto pp = p->getPosition();
		Sphere3dd s(pp, searchRadius * 1.5);
		builder.add(s);
	}

	this->volume = builder.get();

	auto nodes = volume->getNodes();
	std::vector<SparseVolumeNode<double>*> ns(nodes.begin(), nodes.end());
#pragma omp parallel for
	for(int i = 0; i < ns.size(); ++i) {
		auto node = ns[i];
//	for (auto& node : nodes) {
		const auto pos = node->getPosition();
		const auto neighbors = spaceHash.findNeighbors(pos);
		for (auto n : neighbors) {
			auto sp = static_cast<SPHSurfaceParticle*>(n);
			const auto v = n->getPosition() - pos;
			const auto coe = 1400.0f / searchRadius / searchRadius / searchRadius;
			const auto w = coe * kernel.getCubicSpline(v) * sp->getMass() / sp->getDensity();
			node->setValue(w + node->getValue());
		}
	}
}

void SPHSurfaceBuilder::buildAnisotoropic(const std::vector<Vector3dd>& positions, const float particleRadius, const float cellLength)
{
	const auto searchRadius = particleRadius * 2.25f;
	const SPHKernel kernel(searchRadius);

	for (auto p : positions) {
		particles.push_back(std::make_unique<SPHSurfaceParticle>(p, particleRadius));
	}

	calculateAnisotropy(searchRadius);

	CompactSpaceHash3d spaceHash(searchRadius, (int)particles.size());

	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

	/*
	for (const auto& p : particles) {
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
	}
	*/

	this->volume = createSparseVolume(positions, cellLength);


	auto nodes = volume->getNodes();
	/*
	std::vector<SparseVolumeNode<double>*> ns;
	ns.reserve(nodes.size());
	for (auto n : nodes) {
		ns.push_back(n.second);
	}
	*/

	//for (auto& node : nodes) {
//#pragma omp parallel for
	for (auto node : nodes) {
		//auto node = ns[i];
		const auto pos = node->getPosition();
		const auto neighbors = spaceHash.findNeighbors(pos);
		for (auto n : neighbors) {
			auto sp = static_cast<SPHSurfaceParticle*>(n);
			//auto m = sp->getMatrix();
			auto m = Matrix3df(0.5, 0, 0, 0, 0.5, 0, 0, 0, 0.5) / searchRadius;
			const auto v = Vector3dd(sp->getPosition()) - pos;
			const Vector3df distance = m * v;
			//const auto d = glm::length(distance);
			const auto det = glm::determinant(m);
			const auto w = kernel.getCubicSpline(v) * det * sp->getMass() / sp->getDensity();
			node->setValue(w + node->getValue());
			//const auto distance = getDistanceSquared(sp->getPosition(), pos);
		}
		//		n.second->getValue();
	}
}

std::unique_ptr<SparseVolumed> SPHSurfaceBuilder::createSparseVolume(const std::vector<Vector3dd>& particles, const float cellLength)
{
	Vector3dd resolution{ cellLength, cellLength, cellLength };
	auto sv = std::make_unique<SparseVolumed>(resolution, particles.size());
	return sv;
}

void SPHSurfaceBuilder::calculateAnisotropy(const float searchRadius)
{
	const SPHKernel kernel(searchRadius);

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());
	
	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

	for (const auto& p : particles) {
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		p->calculateDensity(neighbors, searchRadius, kernel);
		WPCA wpca;
		wpca.setup(p.get(), neighbors, searchRadius);
		const auto wm = wpca.calculateWeightedMean(p.get(), neighbors, searchRadius);
		p->correctedPosition(0.95, wm);
		p->calculateAnisotoropicMatrix(neighbors, searchRadius);
	}
}
