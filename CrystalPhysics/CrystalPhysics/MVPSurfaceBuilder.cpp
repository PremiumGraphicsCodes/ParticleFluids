#include "MVPSurfaceBuilder.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "Crystal/Util/Array3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSurfaceBuilder::build(const std::vector<MVPVolumeParticle*>& volumeParticles, const unsigned int res, const double threshold)
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

	const auto size = volumeParticles.size();
//#pragma omp parallel for
	for(int i = 0; i < size; ++i) {
		auto vp = volumeParticles[i];
	//for (auto vp : volumeParticles) {
		const auto min = vp->getPositionf() - Vector3df(l, l, l);
		const auto max = vp->getPositionf() + Vector3df(l, l, l);
		const Box3df box(min, max);
		Util::Array3d<MCCell::Vertex> grid(res + 1, res + 1, res + 1);
		for (int i = 0; i <= res; ++i) {
			const auto u = i / 1.0;
			for (int j = 0; j <= res; ++j) {
				const auto v = j / 1.0;
				for (int k = 0; k <= res; ++k) {
					const auto w = k / 1.0;
					const auto p = box.getPosition(u, v, w);
					/*
					const auto ix = int(p.x / radius);
					const auto iy = int(p.y / radius);
					const auto iz = int(p.z / radius);
					std::array<int, 3> index = { ix, iy, iz };
					*/
					const auto c = spaceHash.findNeighbors(p);
					MCCell::Vertex v;
					v.position = p;
					v.value = static_cast<double>(c.size());
					grid.set(i,j,k, v);
				}
			}
		}
		for (int i = 0; i < res; ++i) {
			for (int j = 0; j < res; ++j) {
				for (int k = 0; k < res; ++k) {
					MCCell cell;
					cell.vertices[0] = grid.get(i, j, k);
					cell.vertices[1] = grid.get(i+1, j, k);
					cell.vertices[2] = grid.get(i+1, j+1, k);
					cell.vertices[3] = grid.get(i,   j+1, k);
					cell.vertices[4] = grid.get(i,   j, k+1);
					cell.vertices[5] = grid.get(i+1, j, k+1);
					cell.vertices[6] = grid.get(i+1, j+1, k+1);
					cell.vertices[7] = grid.get(i,   j+1, k+1);
					mc.march(cell, threshold);
				}
			}
		}
	}
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
