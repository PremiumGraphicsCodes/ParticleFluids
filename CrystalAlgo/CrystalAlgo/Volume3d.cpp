#include "Volume3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Algo;

Volume3d::Volume3d(const int u, const int v, const int w, const Box3d& box)
{
	const auto dx = box.getLength().x / (double)u;
	const auto dy = box.getLength().y / (double)v;
	const auto dz = box.getLength().z / (double)w;
	nodes.resize(u);
	for (int i = 0; i < u; ++i) {
		const auto px = box.getMinX() + i * dx;
		nodes[i].resize(v);
		for (int j = 0; j < v; ++j) {
			const auto py = box.getMinY() + j * dy;
			nodes[i][j].resize(w);
			for (int k = 0; k < w; ++k) {
				const auto pz = box.getMinZ() + k * dz;
				nodes[i][j][k] = Shape::Particle<double>(Math::Vector3dd(px, py, pz), 0.0);
			}
		}
	}
}

void Volume3d::set(const int i, const int j, const int k, double value)
{
	nodes[i][j][k].setAttribute(value);
}

std::vector<Particle<double>> Volume3d::toParticles()
{
	std::vector<Particle<double>> results;
	for (const auto& u : nodes) {
		for (const auto& v : u) {
			for (const auto& w : v) {
				results.push_back(w);
			}
		}
	}
	return results;
}