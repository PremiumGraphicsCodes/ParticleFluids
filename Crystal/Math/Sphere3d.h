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

	/*
	Sphere3d(const Math::Box3d& boundingBox) {
		center = boundingBox.getCenter();
		const auto& length = boundingBox.getLength();
		radius = std::min<double>(std::min<double>(length.x, length.y), length.z) * 0.5;
	}
	*/

	Vector3dd getPosition(const double u, const double v) const override {
		const auto theta = u * Tolerance<double>::getPI();
		const auto phi = v * Tolerance<double>::getTwoPI();
		const auto x = radius * std::sin(theta) * std::cos(phi);
		const auto y = radius * std::sin(theta) * std::sin(phi);
		const auto z = radius * std::cos(theta);
		return center + Vector3dd(x, y, z);
	}

	Vector3dd getNormal(const double u, const double v) const {
		const auto& pos = getPosition(u, v);
		return glm::normalize( pos - center );
	}

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

	bool equals(const Sphere3d& rhs, const double tolerance) const {
		return
			Tolerance<double>::isEqual(radius, rhs.radius, tolerance) &&
			(center == rhs.center);
	}

	bool isInner(const Vector3dd& v) const { return glm::distance(v, center) < radius; }

	bool isOuter(const Vector3dd& v) const { return glm::distance(v, center) > radius; }

private:
	Vector3dd center;
	double radius;
};

	}
}

#endif