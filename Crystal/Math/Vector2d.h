#pragma once

#include <cmath>
#include "glm.h"

namespace Crystal {
	namespace Math {

template<typename T>
using Vector2d = glm::vec<2, T>;

using Vector2df = Vector2d<float>;
using Vector2dd = Vector2d<double>;

template<typename T>
static T getDistanceSquared(const Vector2d<T>& v)
{
	return std::pow(v.x, T(2)) + std::pow(v.y, T(2));
}

template<typename T>
static T getDistanceSquared(const Vector2d<T>& lhs, const Vector2d<T>& rhs)
{
	return std::pow(lhs.x - rhs.x, T(2)) + std::pow(lhs.y - rhs.y, T(2));
}

template<typename T>
static T getDistance(const Vector2d<T>& lhs, const Vector2d<T>& rhs)
{
	return std::sqrt(getDistanceSquared(lhs, rhs));
}

template<typename T>
static bool areSame(const Vector2d<T>& lhs, const Vector2d<T>& rhs, const T tolerance)
{
	return getDistanceSquared(lhs, rhs) < tolerance;
}


	}
}