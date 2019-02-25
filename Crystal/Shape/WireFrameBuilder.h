#pragma once

#include "WireFrame.h"
#include "../Math/ICurve3d.h"

namespace Crystal {
	namespace Math {
		class Box3d;
	}
	namespace Shape {

class WireFrameBuilder
{
public:
	void build(const Math::Box3d& box);

	void build(const Math::ICurve3d& sphere, const int unum, const int vnum);

	WireFrame* getWireFrame() const { return new WireFrame(lines); }

private:
	void build(const std::vector<std::vector<Math::Vector3dd>>& grid);

private:
	std::vector<Math::Line3dd> lines;
};
	}
}