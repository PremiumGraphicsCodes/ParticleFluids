#include "MVPSurfaceBuilder.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/MCCell.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSurfaceBuilder::build(const size_t tableSize, const float searchRadius)
{
	//volume.createNode()
	hash.setup(searchRadius * 2.0, tableSize);
}

void MVPSurfaceBuilder::add(MVPMassParticle* massParticle)
{
	hash.add(massParticle);

	//hash.getTable()
}

void MVPSurfaceBuilder::buildVolume()
{
	auto cells = hash.getCells();

	MCCell cell;
	for (auto c : cells) {
		const std::array<unsigned int, 3> ii = c->index;
		const auto i = ii[0];
		const auto j = ii[1];
		const auto k = ii[2];

		std::array< std::array<unsigned int, 3>, 8> indices;
		indices[0] = ii;
		indices[1] = { i+1, j, k };
		indices[2] = { i+1, j+1, k };
		indices[3] = { i, j+1, k };
		indices[4] = { i, j, k + 1 };
		indices[5] = { i + 1, j, k + 1 };
		indices[6] = { i + 1, j + 1, k + 1 };
		indices[7] = { i, j + 1, k + 1 };

		for (int u = 0; u < 8; ++u) {
			const auto index = indices[u];
			const auto cc0 = hash.find(index);
			const auto w0 = static_cast<double>( cc0.size() );
			cell.vertices[u].position = hash.toPosition(index);
			cell.vertices[u].value = w0;
		}
	}
}
