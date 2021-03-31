#include "WireFrameBuilder.h"

#include "../Math/Line3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Ray3d.h"
#include "../Math/Box3d.h"
#include "../Math/Circle3d.h"
#include "../Math/Cone3d.h"
#include "../Math/Cylinder3d.h"

#include "WireFrame.h"
#include "CircularBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

namespace {
	constexpr auto tolerance = 1.e-12;
}

void WireFrameBuilder::build(const ICurve3d& curve, const int unum)
{
	std::vector<int> grid;
	const auto du = 1.0 / static_cast<double>(unum);
	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		grid.push_back( createPosition(curve.getPosition(u)) );
	}
	for (int i = 0; i < grid.size() -1; ++i) {
		edges.push_back(WireFrameEdge(grid[i], grid[i+1]));
	}
}

void WireFrameBuilder::build(const ISurface3d& sphere, const int unum, const int vnum)
{
	const auto du = 1.0 / static_cast<double>(unum);
	const auto dv = 1.0 / static_cast<double>(vnum);

	std::vector<std::vector<int>> grid;
	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		std::vector<int> g;
		for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
			g.push_back( createPosition(sphere.getPosition(u, v)) );
		}
		grid.push_back(g);
	}
	for (int i = 0; i < grid.size()-1; ++i) {
		for (int j = 0; j < grid[i].size()-1; ++j) {
			edges.push_back(WireFrameEdge(grid[i][j], grid[i + 1][j]));
			edges.push_back(WireFrameEdge(grid[i][j], grid[i][j + 1]));
		}
	}
}


void WireFrameBuilder::build(const Box3d& box)
{
	const auto p0 = createPosition(box.getPosition(0, 0, 0));
	const auto p1 = createPosition(box.getPosition(1, 0, 0));
	const auto p2 = createPosition(box.getPosition(1, 1, 0));
	const auto p3 = createPosition(box.getPosition(0, 1, 0));
	const auto p4 = createPosition(box.getPosition(0, 0, 1));
	const auto p5 = createPosition(box.getPosition(1, 0, 1));
	const auto p6 = createPosition(box.getPosition(1, 1, 1));
	const auto p7 = createPosition(box.getPosition(0, 1, 1));

	edges.push_back(WireFrameEdge(p0, p1));
	edges.push_back(WireFrameEdge(p1, p2));
	edges.push_back(WireFrameEdge(p2, p3));
	edges.push_back(WireFrameEdge(p3, p0));

	edges.push_back(WireFrameEdge(p4, p5));
	edges.push_back(WireFrameEdge(p5, p6));
	edges.push_back(WireFrameEdge(p6, p7));
	edges.push_back(WireFrameEdge(p7, p4));

	edges.push_back(WireFrameEdge(p0, p4));
	edges.push_back(WireFrameEdge(p1, p5));
	edges.push_back(WireFrameEdge(p2, p6));
	edges.push_back(WireFrameEdge(p3, p7));
}

void WireFrameBuilder::build(const std::vector<std::vector<int>>& grid)
{
	for (int i = 0; i < grid.size() - 1; ++i) {
		for (int j = 0; j < grid[i].size() - 1; ++j) {
			edges.push_back(WireFrameEdge(grid[i][j], grid[i + 1][j]));
			edges.push_back(WireFrameEdge(grid[i][j], grid[i][j + 1]));
			//lines.push_back(Math::Line3dd(grid[i+1][j], grid[i+1][j + 1]));
			//lines.push_back(Math::Line3dd(grid[i][j+1], grid[i+1][j + 1]));
		}
	}
}

int WireFrameBuilder::createPosition(const Vector3dd& v)
{
	positions.push_back(v);
	return static_cast<int>(positions.size() - 1);
}

std::unique_ptr<WireFrame> WireFrameBuilder::createWireFrame()
{
	return std::make_unique<WireFrame>(positions, edges);
}
