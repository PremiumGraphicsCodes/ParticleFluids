#pragma once

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "WireFrameEdge.h"

namespace Crystal {
	namespace Math {
		class Line3dd;
		class Box3d;
		class Sphere3d;
		class Cone3d;
	}
	namespace Shape {
		class WireFrame;

class WireFrameBuilder
{
public:
	void build(const Math::Line3dd& line);

	void build(const Math::Box3d& box);

	void build(const Math::Sphere3d& sphere, const int unum, const int vnum);

	void build(const Math::Cone3d& cone, const int unum, const int vnum, const int wnum);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

	std::vector<WireFrameEdge> getEdges() const { return edges; }

	int createPosition(const Math::Vector3dd& v);

	std::unique_ptr<WireFrame> createWireFrame();

private:
	void build(const std::vector<std::vector<int>>& grid);

private:
	std::vector<Math::Vector3dd> positions;
	std::vector<WireFrameEdge> edges;
};

	}
}