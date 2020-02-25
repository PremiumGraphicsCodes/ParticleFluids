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

void WireFrameBuilder::build(const Line3dd& line)
{
	const auto p0 = createPosition( line.getStart() );
	const auto p1 = createPosition( line.getEnd() );

	edges.push_back(WireFrameEdge(p0, p1));
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

void WireFrameBuilder::build(const Circle3d& circle, const int unum)
{
	CircularBuffer<int> grid(unum);
	for (auto u = 0; u < unum; ++u) {
		const auto uu = (double)u / (double)unum;
		grid[u] = createPosition(circle.getPosition(uu));
	}
	for (int i = 0; i < unum; ++i) {
		edges.push_back(WireFrameEdge(grid[i], grid[i + 1]));
	}
}

void WireFrameBuilder::build(const Sphere3d& sphere, const int unum, const int vnum)
{
	CircularBuffer<CircularBuffer<int>> grid(unum);
	for (auto u = 0; u < unum; ++u) {
		grid[u].resize(vnum);
		const auto uu = (double)u / (double)(unum-1);
		for (auto v = 0; v < vnum; ++v) {
			const auto vv = (double)v / (double)(vnum-1);
			grid[u][v] = createPosition(sphere.getPosition(uu, vv));
		}
	}
	for (int i = 0; i < unum; ++i) {
		for (int j = 0; j < vnum; ++j) {
			edges.push_back(WireFrameEdge(grid[i][j], grid[i + 1][j]));
			edges.push_back(WireFrameEdge(grid[i][j], grid[i][j + 1]));
		}
	}
}

void WireFrameBuilder::build(const Cone3d& cone, const int unum)
{
	const auto top = createPosition( cone.getPosition(0.0, 1.0) );
	std::vector<int> vertices;
	for (auto u = 0; u < unum; ++u) {
		const auto uu = (double)u / (double)unum;
		vertices.push_back(createPosition(cone.getPosition(uu, 0.0)));
	}
	for (const auto v : vertices) {
		edges.push_back(WireFrameEdge(top, v));
	}
	for (int i = 0; i < vertices.size() - 1; ++i) {
		edges.push_back(WireFrameEdge(vertices[i], vertices[i + 1]));
	}
}

void WireFrameBuilder::build(const Cylinder3d& cylinder, const int unum)
{
	const auto bottomCenter = createPosition(cylinder.getPosition(0.0, 0.0, 0.0));
	const auto topCenter = createPosition(cylinder.getPosition(0.0, 1.0, 0.0));

	std::vector<int> bottoms;
	std::vector<int> tops;
	for (auto u = 0; u < unum; ++u) {
		const auto p = (double)u / (double)unum;
		bottoms.push_back(createPosition(cylinder.getPosition(p, 0.0, 1.0)));
		tops.push_back(createPosition(cylinder.getPosition(p, 1.0, 1.0)));
	}

	// create bottom circle.
	for (auto u = 0; u < unum; ++u) {
		edges.push_back(WireFrameEdge(bottomCenter, bottoms[u]));
	}
	for (auto u = 0; u < unum-1; ++u) {
		edges.push_back(WireFrameEdge(bottoms[u], bottoms[u+1]));
	}

	// create top circle.
	for (auto u = 0; u < unum; ++u) {
		edges.push_back(WireFrameEdge(topCenter, tops[u]));
	}
	for (auto u = 0; u < unum-1; ++u) {
		edges.push_back(WireFrameEdge(tops[u], tops[u+1]));
	}

	// create side.
	for (auto u = 0; u < unum; ++u) {
		edges.push_back(WireFrameEdge(bottoms[u], tops[u]));
	}
}

void WireFrameBuilder::build(const Torus3d& torus, const int unu, const int vnum)
{

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
