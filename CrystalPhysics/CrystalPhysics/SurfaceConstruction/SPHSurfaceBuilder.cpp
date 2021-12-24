
#include "SPHSurfaceBuilder.h"

#include "Crystal/Shape/IParticle.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalSpace/CrystalSpace/SparseVolumeBuilder.h"
#include "CrystalSpace/CrystalSpace/DynamicOctree.h"

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
#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto& p = particles[i];	
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

	std::vector<IParticle*> ps;
	for (const auto& p : particles) {
		ps.push_back(p.get());
	}

	const auto bb = DynamicOctree::calculateBox(ps, cellLength);
	DynamicOctree octree(bb);
	octree.divide(cellLength, ps);
	this->volumes = octree.toVolumes();

	octree.clear();

#pragma omp parallel for
	for (int i = 0; i < volumes.size(); ++i) {
		auto vol = volumes[i];

		const auto res = vol->getResolutions();
		for (int i = 0; i < res[0]; ++i) {
			for (int j = 0; j < res[1]; ++j) {
				for (int k = 0; k < res[2]; ++k) {
					const auto pos = vol->getCellPosition(i, j, k);
					const auto neighbors = spaceHash.findNeighbors(pos);
					for (auto n : neighbors) {
						auto sp = static_cast<SPHSurfaceParticle*>(n);
						const auto v = n->getPosition() - pos;
						const auto coe = 1400.0f / searchRadius / searchRadius / searchRadius;
						const auto w = coe * kernel.getCubicSpline(v) * sp->getMass() / sp->getDensity();
						const auto value = vol->getValue(i, j, k);
						vol->setValue(i, j, k, w + value);
					}
				}
			}
		}
	}
}

void SPHSurfaceBuilder::buildAnisotoropic(const std::vector<Vector3dd>& positions, const float particleRadius, const float cellLength)
{
	const auto searchRadius = particleRadius;
	const SPHKernel kernel(searchRadius);

	for (auto p : positions) {
		particles.push_back(std::make_unique<SPHSurfaceParticle>(p, particleRadius));
	}

	calculateAnisotropy(searchRadius);

	CompactSpaceHash3d spaceHash(searchRadius, (int)particles.size());


	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

	std::vector<IParticle*> ps;
	for (const auto& p : particles) {
		ps.push_back(p.get());
	}

	const auto bb = DynamicOctree::calculateBox(ps, cellLength);
	DynamicOctree octree(bb);
	octree.divide(cellLength, ps);
	this->volumes = octree.toVolumes();

	octree.clear();


#pragma omp parallel for
	for (int i = 0; i < volumes.size(); ++i) {
		auto vol = volumes[i];
		//auto node = ns[i];
		const auto res = vol->getResolutions();
		for (int i = 0; i < res[0]; ++i) {
			for (int j = 0; j < res[1]; ++j) {
				for (int k = 0; k < res[2]; ++k) {
					const auto pos = vol->getCellPosition(i, j, k);
					const auto neighbors = spaceHash.findNeighbors(pos);
					for (auto n : neighbors) {
						auto sp = static_cast<SPHSurfaceParticle*>(n);
						auto m = sp->getMatrix();
						//auto m = Matrix3df(0.5, 0, 0, 0, 0.5, 0, 0, 0, 0.5) / searchRadius;
						const auto v = Vector3dd(sp->getPosition()) - pos;
						const Vector3df distance = m * v;
						//const auto d = glm::length(distance);
						const auto det = glm::determinant(m);
						const auto w = kernel.getCubicSpline(v) * det * sp->getMass() / sp->getDensity();
						const auto value = vol->getValue(i, j, k);
						vol->setValue(i,j,k, w + value);
						//const auto distance = getDistanceSquared(sp->getPosition(), pos);
					}

				}
			}
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

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto& p = particles[i];
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		p->calculateDensity(neighbors, searchRadius, kernel);
		WPCA wpca;
		wpca.setup(p.get(), neighbors, searchRadius);
		const auto wm = wpca.calculateWeightedMean(p.get(), neighbors, searchRadius);
		p->correctedPosition(0.95, wm);
		p->calculateAnisotoropicMatrix(neighbors, searchRadius);
	}
}
