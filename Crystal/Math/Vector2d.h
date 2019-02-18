#ifndef __CRSYTAL_MATH_VECTOR_2D_H__
#define __CRSYTAL_MATH_VECTOR_2D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"
#include "glm.h"

namespace Crystal {
	namespace Math {

using Vector2df = glm::vec2;
using Vector2dd = glm::dvec2;

static double getDistanceSquared(const Vector2dd& v)
{
	return std::pow(v.x, 2) + std::pow(v.y, 2);
}

static double getDistanceSquared(const Vector2dd& lhs, const Vector2dd& rhs)
{
	return std::pow(lhs.x - rhs.x, 2) + std::pow(lhs.y - rhs.y, 2);
}

static bool areSame(const Vector2dd& lhs, const Vector2dd& rhs, const double tolerance)
{
	return getDistanceSquared(lhs, rhs) < tolerance;
}


	}
}

#endif