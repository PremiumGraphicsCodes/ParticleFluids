#pragma once

#include "Vector3d.h"
#include "Matrix3d.h"
#include "Matrix4d.h"
#include "ICurve3d.h"

namespace Crystal {
	namespace Math {
		class Ray3d;

class Line3dd : public ICurve3d
{
public:
	Line3dd();

	Line3dd(const Math::Vector3dd& origin, const Math::Vector3dd& dir);

	static Line3dd fromPoints(const Vector3dd& start, const Vector3dd& end);

	Math::Vector3dd getStart() const { return origin; }

	Math::Vector3dd getEnd() const { return origin + dir; }

	Math::Vector3dd getDirection() const { return dir; }

	double getLength() const { return glm::distance(origin, dir); }

	void move(const Math::Vector3dd& v) { this->origin += v; }

	void transform(const Math::Matrix3dd& m);

	void transform(const Math::Matrix4dd& m);

	Math::Vector3dd getPosition(const double u) const override;

	bool isSame(const Line3dd& rhs, const double tolerance) const;

	Ray3d toRay() const;

private:
	Math::Vector3dd origin;
	Math::Vector3dd dir;
};
	}
}