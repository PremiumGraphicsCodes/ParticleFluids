#pragma once

#include "../Math/ICurve3d.h"
#include "../Math/ISurface3d.h"
#include "../Math/IVolume3d.h"

namespace Crystal {
	namespace Math {
		class Line3dd;
		class Box3d;
	}
	namespace Scene {

class WireFrameBuilder
{
public:
	void build(const Math::Box3d& box);

	void build(const Math::ICurve3d& curve);

	void build(const Math::ISurface3d& curve, const int unum, const int vnum);

	void build(const Math::IVolume3d& curve, const int unum, const int vnum);

	std::vector<Math::Line3dd> getWireFrame() const { return lines; }

private:
	void build(const std::vector<std::vector<Math::Vector3dd>>& grid);

private:
	std::vector<Math::Line3dd> lines;
};
	}
}