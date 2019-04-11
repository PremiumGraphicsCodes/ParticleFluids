#include "WireFrameBuilder.h"

#include "../Math/Line3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Ray3d.h"
#include "../Math/Box3d.h"
#include "../Math/Cone3d.h"
#include "../Math/Cylinder3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

void WireFrameBuilder::build(const Box3d& box)
{
	std::vector<Vector3dd> vertices;
	vertices.push_back(box.getPosition(Vector3dd(0, 0, 0)));
	vertices.push_back(box.getPosition(Vector3dd(1, 0, 0)));
	vertices.push_back(box.getPosition(Vector3dd(1, 1, 0)));
	vertices.push_back(box.getPosition(Vector3dd(0, 1, 0)));
	vertices.push_back(box.getPosition(Vector3dd(0, 0, 1)));
	vertices.push_back(box.getPosition(Vector3dd(1, 0, 1)));
	vertices.push_back(box.getPosition(Vector3dd(1, 1, 1)));
	vertices.push_back(box.getPosition(Vector3dd(0, 1, 1)));

	std::vector<std::vector<Vector3dd>> grid;
	lines.push_back(Line3dd::fromPoints(vertices[0], vertices[1]));
	lines.push_back(Line3dd::fromPoints(vertices[1], vertices[2]));
	lines.push_back(Line3dd::fromPoints(vertices[2], vertices[3]));
	lines.push_back(Line3dd::fromPoints(vertices[3], vertices[0]));

	lines.push_back(Line3dd::fromPoints(vertices[4], vertices[5]));
	lines.push_back(Line3dd::fromPoints(vertices[5], vertices[6]));
	lines.push_back(Line3dd::fromPoints(vertices[6], vertices[7]));
	lines.push_back(Line3dd::fromPoints(vertices[7], vertices[4]));

	lines.push_back(Line3dd::fromPoints(vertices[0], vertices[4]));
	lines.push_back(Line3dd::fromPoints(vertices[1], vertices[5]));
	lines.push_back(Line3dd::fromPoints(vertices[2], vertices[6]));
	lines.push_back(Line3dd::fromPoints(vertices[3], vertices[7]));
}

void WireFrameBuilder::build(const Line3dd& line)
{
	std::vector<Vector3dd> vertices;
	vertices.push_back(line.getStart());
	vertices.push_back(line.getEnd());
	lines.push_back(Line3dd::fromPoints(vertices[0], vertices[1]));
}

void WireFrameBuilder::build(const ICurve3d& sphere, const int unum, const int vnum)
{
	const auto du = 1.0 / unum;
	const auto dv = 1.0 / vnum;
	std::vector<std::vector<Math::Vector3dd>> grid;
	for (auto u = 0.0; u < 1.0 + 1.0e-12; u += du) {
		std::vector<Math::Vector3dd> g;
		for (auto v = 0.0; v < 1.0 + 1.0e-12; v += dv) {
			g.push_back(sphere.getPosition(u, v));
		}
		grid.push_back(g);
	}
	build(grid);
}

void WireFrameBuilder::build(const std::vector<std::vector<Vector3dd>>& grid)
{
	for (int i = 0; i < grid.size() - 1; ++i) {
		for (int j = 0; j < grid[i].size() - 1; ++j) {
			lines.push_back(Math::Line3dd(grid[i][j], grid[i + 1][j] - grid[i][j]));
			lines.push_back(Math::Line3dd(grid[i][j], grid[i][j + 1] - grid[i][j]));
			//lines.push_back(Math::Line3dd(grid[i+1][j], grid[i+1][j + 1]));
			//lines.push_back(Math::Line3dd(grid[i][j+1], grid[i+1][j + 1]));
		}
	}
}
