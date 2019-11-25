#pragma once

#include "IShape.h"

#include "../Math/Line3d.h"
#include "WireFrameEdge.h"

namespace Crystal {
	namespace Scene {

class WireFrame : public IShape
{
public:
	WireFrame()
	{}

	WireFrame(const std::vector<Math::Vector3dd>& positions, const std::vector<WireFrameEdge>& edges) :
		positions(positions),
		edges(edges)
	{}

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	void clear() {
		positions.clear();
		edges.clear();
	}

	Math::Box3d getBoundingBox() const override;

private:
	std::vector<Math::Vector3dd> positions;
	std::vector<WireFrameEdge> edges;
};

	}
}