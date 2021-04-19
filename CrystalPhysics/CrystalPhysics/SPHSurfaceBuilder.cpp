
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
	for (auto p : positions) {
		particles.push_back(std::make_unique<SPHSurfaceParticle>(p));
	}

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());
	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

	std::vector<Math::Matrix3dd> matrices;
	for (const auto& p : particles) {
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		p->calculateAnisotoropicMatrix(neighbors, searchRadius);
		p->calculateCorrectedPosition(0.95);
	}

	this->volume = createSparseVolume(positions, searchRadius, cellLength);

	const SPHKernel kernel(searchRadius);

	auto& nodes = volume->getNodes();
	std::vector<SparseVolumeNode*> ns;
	ns.reserve(nodes.size());
	for (auto n : nodes) {
		ns.push_back(n.second);
	}

	//for (auto& node : nodes) {
#pragma omp parallel for
	for(int i = 0; i < ns.size(); ++i){
		auto node = ns[i];
		const auto pos = node->getPosition();
		const auto neighbors = spaceHash.findNeighbors( pos );
		for (auto n : neighbors) {
			auto sp = static_cast<SPHSurfaceParticle*>(n);
			auto m = sp->matrix;
			const auto v = Vector3dd(sp->getCorrectedPosition()) - pos;
			const auto distance = m * v;
			const auto w = kernel.getCubicSpline(distance) * glm::determinant(m);
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