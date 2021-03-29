
#include "SPHSurfaceBuilder.h"

#include "../../Crystal/Shape/IParticle.h"
#include "../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "../../CrystalSpace/CrystalSpace/SparseVolume.h"

#include <set>
//#include <map>

#include "WPCA.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void SPHSurfaceBuilder::add(IParticle* particle)
{
	this->particles.push_back(particle);
}

void SPHSurfaceBuilder::build(const float searchRadius)
{
	Box3d bb = Box3d::createDegeneratedBox();
	for (auto p : particles) {
		bb.add(p->getPosition());
	}

	const auto length = bb.getLength();
	const auto resx = static_cast<int>( length.x / searchRadius );
	const auto resy = static_cast<int>( length.y / searchRadius );
	const auto resz = static_cast<int>( length.z / searchRadius );

	std::set<std::array<int, 3>> indices;
	for (auto p : particles) {
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

	const auto nodes = sv.getNodes();

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());
	for (auto p : particles) {
		spaceHash.add(p);
	}

	for (auto n : nodes) {
		auto p = n.second;
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		WPCA wpca;
		const auto matrix = wpca.calculate(p, neighbors, searchRadius);
	}
}
