#pragma once

#include "Vector3d.h"
#include "IVolume3d.h"

namespace Crystal {
	namespace Math {
		class Box3d;

class Sphere3d : public IVolume3d
{
public:
	Sphere3d() :
		center(Vector3dd(0, 0, 0)),
		radius(1.0f)
	{}

	Sphere3d(const Vector3dd& center, const double radius) :
		center(center),
		radius(radius)
	{}

	explicit Sphere3d(const Math::Box3d& boundingBox);

	Vector3dd getPosition(const Vector3dd& p) const override;

	Vector3dd getNormal(const Math::Vector2dd& p) const override
	{
		return getPosition(Vector3dd(p, 1.0) - Vector3dd(p, 0.0));
	}

	Vector3dd getNormal(const double u, const double v) const;

	Vector3dd getCenter() const { return center; }

	double getRadius() const { return radius; }

	bool isValid(const double tolerance) const { return radius >= tolerance;  }

	void outerOffset(const float offsetLength) { this->radius += offsetLength; }

	void innerOffset(const float offsetLength) { this->radius -= offsetLength; }

	bool isSame(const Sphere3d& rhs, const double tolerance) const;

	bool isInside(const Vector3dd& v) const { return glm::distance(v, center) < radius; }

	bool isOutside(const Vector3dd& v) const { return glm::distance(v, center) > radius; }

	void moveTo(const Vector3dd& pos) { this->center = pos; }

private:
	Vector3dd center;
	double radius;
};

	}
}
