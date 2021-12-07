#include "MVPSurfaceBuilder.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "Crystal/Util/Array3d.h"
#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

namespace {
	struct ZIndexedCell {
		unsigned int zIndex;
		std::array<int, 3> index;
		float value;

		bool operator<(const ZIndexedCell& rhs) {
			return zIndex < rhs.zIndex;
		}
	};

}

void MVPSurfaceBuilder::build(const std::vector<MVPVolumeParticle*>& volumeParticles, const int res, const double threshold)
{
	if (volumeParticles.empty()) {
		return;
	}
	const auto radius = volumeParticles.front()->getRadius();
	const auto tableSize = volumeParticles.size() * volumeParticles.front()->getMassParticles().size();
	CompactSpaceHash3d spaceHash;
	spaceHash.setup(radius, tableSize);
	for (auto vp : volumeParticles) {
		const auto& mps = vp->getMassParticles();
		for (auto mp : mps) {
			spaceHash.add(mp);
		}
	}
	const auto r = radius;
	const auto l = r * 2.0f;

	SparseVolumef sp(Vector3df(radius), tableSize);

	const auto size = volumeParticles.size();
//#pragma omp parallel for
	for (int i = 0; i < size; ++i) {
		auto vp = volumeParticles[i];
		//for (auto vp : volumeParticles) {
		const auto min = vp->getPositionf() - Vector3df(l, l, l);
		const auto max = vp->getPositionf() + Vector3df(l, l, l);
		const Box3df box(min, max);
		Util::Array3d<MCCell::Vertex> grid(res + 1, res + 1, res + 1);
		const auto index = spaceHash.toIndex(vp->getPosition());
		for (int i = -res; i <= res; ++i) {
			for (int j = -res; j <= res; ++j) {
				for (int k = -res; k <= res; ++k) {
					std::array<int, 3> ix = { index[0] + i, index[1] + j, index[2] + k };
					if (!sp.exists(ix)) {
						sp.createNode(ix);
					}
				}
			}
		}
	}

	const auto nodes= sp.getNodes();
	for (auto node : nodes) {
		const auto p = node->getPosition();
		const auto count = float( spaceHash.findNeighbors(p).size() );
		node->setValue(count);
	}

	for (auto node : nodes) {
		const auto ii = node->getIndex();

		const auto i = ii[0];
		const auto j = ii[1];
		const auto k = ii[2];

		std::array<std::array<int, 3>,8> indices;
		indices[0] = { i,j,k };
		indices[1] = { i + 1,j,k };
		indices[2] = { i + 1, j + 1,k };
		indices[3] = { i,j + 1,k };
		indices[4] = { i,j,k+1 };
		indices[5] = { i + 1,j,k+1 };
		indices[6] = { i + 1, j + 1,k+1 };
		indices[7] = { i,j + 1,k+1 };

		MCCell cell;
		for (int i = 0; i < 8; ++i) {
			const auto c = sp.findNode(indices[i]);
			if (c == nullptr) {
				continue;
			}
			cell.vertices[i].position = Vector3dd( c->getPosition() );
			cell.vertices[i].value = c->getValue();
		}
		mc.march(cell, threshold);
	}

	/*
	const auto size = volumeParticles.size();
	//#pragma omp parallel for
	for (int i = 0; i < size; ++i) {
		auto vp = volumeParticles[i];
		//for (auto vp : volumeParticles) {
		const auto min = vp->getPositionf() - Vector3df(l, l, l);
		const auto max = vp->getPositionf() + Vector3df(l, l, l);
		const Box3df box(min, max);

		const auto p = vp->getPosition();
		const auto ix = int(p.x / radius);
		const auto iy = int(p.y / radius);
		const auto iz = int(p.z / radius);
		std::array<int, 3> index = { ix, iy, iz };

		Util::Array3d<MCCell::Vertex> grid(res * 2 + 1, res * 2 + 1, res * 2 + 1);
		for (int i = -(int)res; i <= res; ++i) {
			for (int j = -(int)res; j <= res; ++j) {
				for (int k = -(int)res; k <= res; ++k) {
					const auto p = spaceHash.toPosition({ ix + i, iy + j, iz + k });
					const auto c = spaceHash.find(p);
					MCCell::Vertex v;
					v.position = p;
					v.value = static_cast<double>(c.size());
					grid.set(i + res, j + res, k + res, v);
				}
			}
		}
		for (int i = 0; i < res * 2; ++i) {
			for (int j = 0; j < res * 2; ++j) {
				for (int k = 0; k < res * 2; ++k) {
					MCCell cell;
					cell.vertices[0] = grid.get(i, j, k);
					cell.vertices[1] = grid.get(i + 1, j, k);
					cell.vertices[2] = grid.get(i + 1, j + 1, k);
					cell.vertices[3] = grid.get(i, j + 1, k);
					cell.vertices[4] = grid.get(i, j, k + 1);
					cell.vertices[5] = grid.get(i + 1, j, k + 1);
					cell.vertices[6] = grid.get(i + 1, j + 1, k + 1);
					cell.vertices[7] = grid.get(i, j + 1, k + 1);
					mc.march(cell, threshold);
				}
			}
		}
	}
	*/
}

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
