#ifndef __CRSYTAL_MATH_VECTOR_3D_H__
#define __CRSYTAL_MATH_VECTOR_3D_H__

#include <cmath>
#include <vector>
#include <array>
#include "Tolerance.h"
#include "glm.h"

namespace Crystal {
	namespace Math {

using Vector3df = glm::vec3;
using Vector3dd = glm::dvec3;

static float getLengthSquared(const Vector3df& v)
{
	return v.x * v.x + v.y* v.y + v.z * v.z;
}

static float getLength(const Vector3df& v)
{
	return std::sqrt(getLengthSquared(v));
}

static double getDistanceSquared(const Vector3dd& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

static float getDistanceSquared(const Vector3df& lhs, const Vector3df& rhs)
{
	const auto x = lhs.x - rhs.x;
	const auto y = lhs.y - rhs.y;
	const auto z = lhs.z - rhs.z;
	return x * x + y * y + z * z;
}

static float getDistance(const Vector3df& lhs, const Vector3df& rhs)
{
	return std::sqrt(getDistanceSquared(lhs, rhs));
}

static double getDistanceSquared(const Vector3dd& lhs, const Vector3dd& rhs)
{
	const auto x = lhs.x - rhs.x;
	const auto y = lhs.y - rhs.y;
	const auto z = lhs.z - rhs.z;
	return x*x + y*y + z*z;
}

static bool areSame(const Vector3dd& lhs, const Vector3dd& rhs, const double tolerance)
{
	return getDistanceSquared(lhs, rhs) < tolerance;
}

template<typename T>
static auto getDistanceSquared(const T& lhs, const T rhs)
{
	return getDistanceSquared(lhs, rhs);
}

	}
}

#endif