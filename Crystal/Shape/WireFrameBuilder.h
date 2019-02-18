#pragma once

#include "../Math/Line3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Box3d.h"
#include "WireFrame.h"

namespace Crystal {
	namespace Shape {

class WireFrameBuilder
{
public:
	void build(const Math::Box3d& box);

	void build(const Math::Sphere3d& sphere);

	void make(const std::vector<std::vector<Math::Vector3dd>>& grid);

	WireFrame* getWireFrame() const { return new WireFrame(lines); }

private:
	std::vector<Math::Line3dd> lines;
};
	}
}