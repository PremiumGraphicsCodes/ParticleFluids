#pragma once

#include <vector>
#include <memory>

#include "../Math/ICurve3d.h"

#include "../Math/Vector3d.h"
#include "WireFrameEdge.h"

namespace Crystal {
	namespace Math {
		class Box3d;
		class ISurface3d;
	}
	namespace Shape {
		class WireFrame;

class WireFrameBuilder
{
public:
	void build(const Math::ICurve3dd& curve, int unum);

	void build(const Math::ISurface3d& circle, const int unum, const int vnum);

	void build(const Math::Box3d& box);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

	std::vector<WireFrameEdge> getEdges() const { return edges; }

	int createPosition(const Math::Vector3dd& v);

	void addEdge(const WireFrameEdge& e) { this->edges.push_back(e); }

	std::unique_ptr<WireFrame> createWireFrame();

private:
	void build(const std::vector<std::vector<int>>& grid);

private:
	std::vector<Math::Vector3dd> positions;
	std::vector<WireFrameEdge> edges;
};

	}
}