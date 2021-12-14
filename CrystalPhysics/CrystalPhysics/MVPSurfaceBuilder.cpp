#include "MVPSurfaceBuilder.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "Crystal/Util/Array3d.h"
#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSurfaceBuilder::build(const std::vector<MVPVolumeParticle*>& volumeParticles, const int res, const double threshold)
{
	if (volumeParticles.empty()) {
		return;
	}
	std::vector<Vector3dd> vps;
	std::vector<Vector3dd> massParticles;
	for (auto vp : volumeParticles) {
		vps.push_back(vp->getPosition());
		const auto mps = vp->getMassParticles();
		for (auto mp : mps) {
			massParticles.push_back(mp->getPosition());
		}
	}
	const auto radius = volumeParticles.front()->getRadius();
	buildVolumes(vps, radius, res);
	buildMasses(massParticles, radius);
	buildCells(threshold);
}

void MVPSurfaceBuilder::buildVolumes(const std::vector<Vector3dd>& positions, const double radius, const int res)
{
	if (positions.empty()) {
		return;
	}
	const auto r = radius;
	//const auto l = r * 2.0f;

	const auto tableSize = static_cast<int>(positions.size());
	this->sparseVolume = std::make_unique<SparseVolumef>(Vector3df(radius), tableSize);

	for (int i = 0; i < positions.size(); ++i) {
		auto vp = positions[i];
		const auto index = this->sparseVolume->toIndex(vp);
		for (int i = -res; i <= res; ++i) {
			for (int j = -res; j <= res; ++j) {
				for (int k = -res; k <= res; ++k) {
					std::array<int, 3> ix = { index[0] + i, index[1] + j, index[2] + k };
					if (!this->sparseVolume->exists(ix)) {
						this->sparseVolume->createNode(ix);
					}
				}
			}
		}
	}
}

void MVPSurfaceBuilder::buildMasses(const std::vector<Vector3dd>& massParticles, const double radius)
{
	ParticleSystem<float> ps(massParticles, 0.0f);
	auto pts = ps.getIParticles();

	const int tableSize = massParticles.size();

	CompactSpaceHash3d spaceHash;
	spaceHash.setup(radius, tableSize);
	for (auto mp : pts) {
		spaceHash.add(mp);
	}

	const auto nodes = this->sparseVolume->getNodes();
	for (auto node : nodes) {
		const auto p = node->getPosition();
		const auto count = float(spaceHash.findNeighbors(p).size());
		node->setValue(count);
	}

	for (auto node : nodes) {
		const auto ii = node->getIndex();

		const auto i = ii[0];
		const auto j = ii[1];
		const auto k = ii[2];

		std::array<std::array<int, 3>, 8> indices;
		indices[0] = { i,j,k };
		indices[1] = { i + 1,j,k };
		indices[2] = { i + 1, j + 1,k };
		indices[3] = { i,j + 1,k };
		indices[4] = { i,j,k + 1 };
		indices[5] = { i + 1,j,k + 1 };
		indices[6] = { i + 1, j + 1,k + 1 };
		indices[7] = { i,j + 1,k + 1 };

		MCCell cell;
		for (int i = 0; i < 8; ++i) {
			const auto c = this->sparseVolume->findNode(indices[i]);
			if (c == nullptr) {
				cell.vertices[i].position = this->sparseVolume->getPositionAt(indices[i]);
				cell.vertices[i].value = 0.0f;
			}
			else {
				//const auto px = indices[i][0] * radius;
				//const auto py = indices[i][1] * radius;
				//const auto pz = indices[i][2] * radius;
				cell.vertices[i].position = Vector3dd(c->getPosition());
				cell.vertices[i].value = c->getValue();
			}
		}
		mcCells.push_back(cell);
	}
}

void MVPSurfaceBuilder::buildCells(const double threshold)
{
	for (const auto& cell : mcCells) {
		mc.march(cell, threshold);
	}
}