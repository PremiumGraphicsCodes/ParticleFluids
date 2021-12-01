#include "MVPSurfaceBuilder.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSurfaceBuilder::build(const std::vector<Vector3dd>& positions, const double radius, const double threshold)
{
	CompactSpaceHash3d spaceHash;
	spaceHash.setup(radius, positions.size());
	ParticleSystem<float> ps;
	for (auto p : positions) {
		ps.add(p, 0.0);
	}
	auto particles = ps.getIParticles();
	for (auto p : particles) {
		spaceHash.add(p);
	}
	build(spaceHash, threshold);
}

void MVPSurfaceBuilder::build(const CompactSpaceHash3d& hash, const double threshold)
{
	auto cells = hash.getCells();

	for (auto c : cells) {
		const std::array<int, 3> ii = c->index;
		const auto i = ii[0];
		const auto j = ii[1];
		const auto k = ii[2];

		std::array< std::array<int, 3>, 8> indices;
		indices[0] = ii;
		indices[1] = { i+1, j, k };
		indices[2] = { i+1, j+1, k };
		indices[3] = { i, j+1, k };
		indices[4] = { i, j, k + 1 };
		indices[5] = { i + 1, j, k + 1 };
		indices[6] = { i + 1, j + 1, k + 1 };
		indices[7] = { i, j + 1, k + 1 };

		MCCell mcCell;
		for (int u = 0; u < 8; ++u) {
			const auto index = indices[u];
			const auto cc0 = hash.find(index);
			const auto w0 = static_cast<double>( cc0.size() );
			mcCell.vertices[u].position = hash.toPosition(index);
			mcCell.vertices[u].value = w0;
		}
		mc.march(mcCell, threshold);
	}
}
