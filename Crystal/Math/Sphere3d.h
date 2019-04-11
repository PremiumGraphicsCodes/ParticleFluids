#ifndef __CRYSTAL_MATH_SPHERE_H__
#define __CRYSTAL_MATH_SPHERE_H__

#include "Vector3d.h"
#include "ICurve3d.h"

#include <vector>
#include <cassert>
#include <algorithm>

namespace Crystal {
	namespace Math {
		class Box3d;

class Sphere3d : public ICurve3d
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

	Vector3dd getPosition(const double u, const double v) const override;

	Vector3dd getNormal(const double u, const double v) const;

	Vector3dd getCenter() const { return center; }

	double getRadius() const { return radius; }

	bool isValid() const {
		return radius >= 0.0f;
	}

	void outerOffset(const float offsetLength) {
		this->radius += offsetLength;
		assert(isValid());
	}

	Sphere3d getOuterOffset(const float offsetLength) const {
		Sphere3d sphere = *this;
		sphere.radius += offsetLength;
		assert(sphere.isValid());
		return sphere;
	}

	void innerOffset(const float offsetLength) {
		this->radius -= offsetLength;
		assert(isValid());
	}

	Sphere3d getInnerOffset(const float offsetLength) const {
		Sphere3d sphere = *this;
		sphere.radius -= offsetLength;
		assert(sphere.isValid());
		return sphere;
	}

	bool isSame(const Sphere3d& rhs, const double tolerance) const;

	bool isInner(const Vector3dd& v) const { return glm::distance(v, center) < radius; }

	bool isOuter(const Vector3dd& v) const { return glm::distance(v, center) > radius; }

private:
	Vector3dd center;
	double radius;
};

	}
}

#endif