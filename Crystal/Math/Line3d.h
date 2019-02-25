#pragma once

#include "Vector3d.h"
#include "Matrix3d.h"
#include "Matrix4d.h"

namespace Crystal {
	namespace Math {

class Line3dd
{
public:
	Line3dd() :
		origin(0,0,0),
		dir(1,0,0)
	{
	}

	Line3dd(const Math::Vector3dd& origin, const Math::Vector3dd& dir) :
		origin(origin),
		dir(dir)
	{
	}

	static Line3dd fromPoints(const Vector3dd& start, const Vector3dd& end)
	{
		return Line3dd(start, end - start);
	}

	Math::Vector3dd getStart() const { return origin; }

	Math::Vector3dd getEnd() const { return origin + dir; }

	Math::Vector3dd getDirection() const { return dir; }

	double getLength() const { return glm::distance(origin, dir); }

	void move(const Math::Vector3dd& v) { this->origin += v; }

	void transform(const Math::Matrix3dd& m) { dir = m * dir; }

	void transform(const Math::Matrix4dd& m) { dir = m * glm::vec4(dir,1.0); }

private:
	Math::Vector3dd origin;
	Math::Vector3dd dir;
};
	}
}