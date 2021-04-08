
#include "SPHSurfaceBuilder.h"

#include "../../Crystal/Shape/IParticle.h"
#include "../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "../../CrystalSpace/CrystalSpace/SparseVolume.h"

#include "../../CrystalNumerics/CrystalNumerics/SVD.h"

#include <set>
//#include <map>

#include "WPCA.h"
#include "SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

/*
void SPHSurfaceBuilder::add(IParticle* particle)
{
	this->particles.push_back(particle);
}
*/

namespace {
	constexpr auto kr = 4.0;
	constexpr auto ks = 1400.0;
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
		calculateAnisotoropicMatrix(p.get(), neighbors, searchRadius);
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
			const auto v = n->getPosition() - pos;
			const auto distance = m * v;
			const auto w = kernel.getCubicSpline(distance);
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

void SPHSurfaceBuilder::calculateAnisotoropicMatrix(SPHSurfaceParticle* p, const std::vector<IParticle*>& neighbors, const float searchRadius)
{
	//const Matrix3dd scaleMatrix;
	WPCA wpca;
	const auto matrix = wpca.calculate(p, neighbors, searchRadius);
	Crystal::Numerics::SVD svd;
	auto result = svd.calculateJacobi(matrix);
	/*
	if (!result.isOk) {
		p->matrix = ::identitiyMatrix();
		return;
	}
	*/

	const auto rotation = result.eigenVectors;


	Matrix3dd scaleMatrix = ::identitiyMatrix();
	if (neighbors.size() < 25) {
		scaleMatrix *= 0.5;
//		p->matrix = scaleMatrix;
	}
	else {
		auto evs = result.eigenValues;
		evs[1] = std::max(evs[1], evs[0] / kr);
		evs[2] = std::max(evs[2], evs[0] / kr);
//		evs /= 14.0;//ks;

		scaleMatrix = Matrix3dd
		(
			evs[0], 0.0, 0.0,
			0.0, evs[1], 0.0,
			0.0, 0.0, evs[2]
		);
	}
	p->matrix = rotation * scaleMatrix * glm::transpose(rotation) * (1.0 / searchRadius);

}

// calculateRotationMatrix()
// calculateScaleMatrix()