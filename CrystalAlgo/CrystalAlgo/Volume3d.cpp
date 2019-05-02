#include "Volume3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Algo;

Volume3d::Volume3d(const int unum, const int vnum, const int wnum, const Box3d& box) :
	unum(unum),
	vnum(vnum),
	wnum(wnum),
	boundingBox(box)
{
	const auto dx = box.getLength().x / (double)unum;
	const auto dy = box.getLength().y / (double)vnum;
	const auto dz = box.getLength().z / (double)wnum;
	nodes.resize(unum);
	for (int u = 0; u < unum; ++u) {
		const auto px = box.getMinX() + u * dx;
		nodes[u].resize(vnum);
		for (int v = 0; v < vnum; ++v) {
			const auto py = box.getMinY() + v * dy;
			nodes[u][v].resize(wnum);
			for (int w = 0; w < wnum; ++w) {
				const auto pz = box.getMinZ() + w * dz;
				nodes[u][v][w] = Shape::Particle<double>(Math::Vector3dd(px, py, pz), 0.0);
			}
		}
	}
}

void Volume3d::add(const std::function<double(double)>& function)
{
	const auto& center = getBoundingBox().getCenter();
	for (auto& u : nodes) {
		for (auto& v : u) {
			for (auto& w : v) {
				auto distance = glm::distance( w.getPosition(), center );
				auto value = function(distance);
				w.setAttribute(w.getAttribute() + value);
			}
		}
	}
}

void Volume3d::set(const int u, const int v, const int w, const double value)
{
	nodes[u][v][w].setAttribute(value);
}

std::vector<Particle<double>> Volume3d::toParticles() const
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