
#include "SPHSurfaceBuilder.h"

#include "../../Crystal/Shape/IParticle.h"
#include "../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "../../CrystalSpace/CrystalSpace/SparseVolume.h"

#include <set>
//#include <map>

#include "WPCA.h"
#include "SPHKernel.h"

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
			return (std::pow(2 - q, 3) / 6.0f);
		}
		else {
			return 0;
		}
	}
}

void SPHSurfaceBuilder::buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float searchRadius)
{
	for (auto p : positions) {
		particles.push_back(std::make_unique<SPHSurfaceParticle>(p));
	}

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());
	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

	this->volume = createSparseVolume(positions, searchRadius, searchRadius);

	const SPHKernel kernel(searchRadius);

	auto& nodes = volume->getNodes();
	for (auto& node : nodes) {
		const auto pos = node.second->getPosition();
		const auto neighbors = spaceHash.findNeighbors(pos);
		for (auto n : neighbors) {
			auto sp = static_cast<SPHSurfaceParticle*>(n);
			const auto v = n->getPosition() - pos;
			const auto w = kernel.getCubicSpline(v);
			node.second->setValue(w + node.second->getValue());
		}
	}
}

void SPHSurfaceBuilder::buildAnisotoropic(const std::vector<Vector3dd>& positions, const float searchRadius, const float cellLength)
{
	const SPHKernel kernel(searchRadius);

	for (auto p : positions) {
		particles.push_back(std::make_unique<SPHSurfaceParticle>(p));
	}

	calculateAnisotropy(searchRadius);

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());

	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

	for (const auto& p : particles) {
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		p->calculateAnisotoropicMatrix(neighbors, searchRadius);
	}

	this->volume = createSparseVolume(positions, searchRadius, cellLength);


	auto& nodes = volume->getNodes();
	std::vector<SparseVolumeNode*> ns;
	ns.reserve(nodes.size());
	for (auto n : nodes) {
		ns.push_back(n.second);
	}

	//for (auto& node : nodes) {
#pragma omp parallel for
	for (int i = 0; i < ns.size(); ++i) {
		auto node = ns[i];
		const auto pos = node->getPosition();
		const auto neighbors = spaceHash.findNeighbors(pos);
		for (auto n : neighbors) {
			auto sp = static_cast<SPHSurfaceParticle*>(n);
			auto m = sp->getMatrix();
			//auto m = Matrix3df(1.0, 0, 0, 0, 1, 0, 0, 0, 1) / searchRadius;
			const auto v = Vector3dd(sp->getPosition()) - pos;
			const auto distance = m * v;
			const auto d = glm::length(distance);
			const auto det = glm::determinant(m);
			const auto w = ::getCubicSpline(d, searchRadius) * det / sp->getDensity();
			node->setValue(w + node->getValue());
			//const auto distance = getDistanceSquared(sp->getPosition(), pos);
		}
		//		n.second->getValue();
	}
}

std::unique_ptr<SparseVolume> SPHSurfaceBuilder::createSparseVolume(const std::vector<Vector3dd>& particles, const float searchRadius,  const float cellLength)
{
	Box3d bb = Box3d::createDegeneratedBox();
	for (const auto& p : particles) {
		bb.add(p);
	}

	bb.add(bb.getMin() - Vector3dd(cellLength));
	bb.add(bb.getMax() + Vector3dd(cellLength));

	const auto origin = bb.getMin();

	const auto length = bb.getLength();
	const auto resx = static_cast<int>(length.x / cellLength);
	const auto resy = static_cast<int>(length.y / cellLength);
	const auto resz = static_cast<int>(length.z / cellLength);

	const auto i = static_cast<int>( searchRadius / cellLength );

	std::set<std::array<int, 3>> indices;
	for (const auto& p : particles) {
		const auto localPosition = p - origin;
		const auto ip = localPosition / (double)cellLength;
		for (int ix = -i; ix <= i; ix++) {
			for (int iy = -i; iy <= i; iy++) {
				for (int iz = -i; iz <= i; iz++) {
					std::array<int, 3> index = { ip[0] + ix, ip[1] + iy, ip[2] + iz };
					indices.insert(index);
				}
			}
		}
	}

	std::array<int, 3> resolution{ resx, resy, resz };
	auto sv = std::make_unique<SparseVolume>(bb, resolution);
	for (const auto& index : indices) {
		sv->createNode(index);
	}
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
	}
}
