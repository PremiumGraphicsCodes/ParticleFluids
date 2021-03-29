
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

void SPHSurfaceBuilder::build(const std::vector<Vector3dd>& positions, const float searchRadius)
{
	std::vector<std::unique_ptr<SPHSurfaceParticle>> particles;
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
		if (neighbors.size() < 2) {
			p->matrix = ::identitiyMatrix();
			continue;
		}
		WPCA wpca;
		const auto matrix = wpca.calculate(p.get(), neighbors, searchRadius);
		Crystal::Numerics::SVD svd;
		auto result = svd.calculate(matrix);
		if (!result.isOk) {
			p->matrix = ::identitiyMatrix();
			continue;
		}
		p->matrix = result.eigenVectors;
		auto evs = result.eigenValues;
		evs[1] = std::max(evs[1], evs[0] / kr);
		evs[2] = std::max(evs[2], evs[0] / kr);
		evs *= ks;

		Matrix3dd diagonalMatrix(
			evs[0], 0.0, 0.0,
			0.0, evs[1], 0.0,
			0.0, 0.0, evs[2]
		);
		p->matrix = p->matrix * diagonalMatrix * glm::transpose(p->matrix) * (1.0 / searchRadius);
	}

	Box3d bb = Box3d::createDegeneratedBox();
	for (const auto& p : particles) {
		bb.add(p->getPosition());
	}

	const auto length = bb.getLength();
	const auto resx = static_cast<int>( length.x / searchRadius );
	const auto resy = static_cast<int>( length.y / searchRadius );
	const auto resz = static_cast<int>( length.z / searchRadius );

	std::set<std::array<int, 3>> indices;
	for (const auto& p : particles) {
		const auto index = p->getPosition() / (double)searchRadius;
		for (int ix = index.x - 1; ix <= index.x + 1; ix++) {
			for (int iy = index.y - 1; iy <= index.y + 1; iy++) {
				for (int iz = index.z - 1; iz <= index.z + 1; iz++) {
					std::array<int, 3> index = { ix, iy, iz };
					indices.insert(index);
//					sv.
				}
			}
		}
	}

	SparseVolume sv(bb, { resx, resy, resz });
	for (const auto& index : indices) {
		sv.createNode(index);
	}

	SPHKernel kernel(searchRadius);

	const auto nodes = sv.getNodes();
	for (auto& node : nodes) {
		const auto pos = node.second->getPosition();
		const auto neighbors = spaceHash.findNeighbors( pos );
		for (auto n : neighbors) {
			auto sp = static_cast<SPHSurfaceParticle*>(n);
			auto m = sp->matrix;
			const auto v = n->getPosition() - pos;
			const auto distance = m * v;
			const auto w = kernel.getCubicSpline(distance);
			node.second->setValue(w + node.second->getValue());
			//const auto distance = getDistanceSquared(sp->getPosition(), pos);
		}
//		n.second->getValue();
	}

}
