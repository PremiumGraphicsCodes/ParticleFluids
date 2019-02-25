#pragma once

#include "WireFrame.h"

namespace Crystal {
	namespace Math {
		class Box3d;
		class Sphere3d;
		class Cone3d;
	}
	namespace Shape {

class WireFrameBuilder
{
public:
	void build(const Math::Box3d& box);

	void build(const Math::Sphere3d& sphere, const int unum, const int vnum);

	void build(const Math::Cone3d& cone);

	WireFrame* getWireFrame() const { return new WireFrame(lines); }

private:
	void build(const std::vector<std::vector<Math::Vector3dd>>& grid);

private:
	std::vector<Math::Line3dd> lines;
};
	}
}