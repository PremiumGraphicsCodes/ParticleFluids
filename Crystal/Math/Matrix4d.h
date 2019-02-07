#ifndef __CRYSTAL_MATH_MATRIX_4D_H__
#define __CRYSTAL_MATH_MATRIX_4D_H__

#include <cassert>
#include <array>
#include "../ThirdParty/glm-0.9.8.5/glm/glm.hpp"

namespace Crystal {
	namespace Math {

using Matrix4df = glm::mat4;
using Matrix4dd = glm::dmat4;

static Matrix4dd rotateX(double angle)
{
	return Matrix4dd
	(
		1.0, 0.0, 0.0, 0.0,
		0.0, ::cos(angle), -::sin(angle), 0.0,
		0.0, ::sin(angle), ::cos(angle), 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}

static Matrix4dd rotateY(double angle)
{
	return Matrix4dd
	(
		::cos(angle), 0.0, ::sin(angle), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-::sin(angle), 0.0, ::cos(angle), 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}

static Matrix4dd rotateZ(double angle)
{
	return Matrix4dd
	(
		::cos(angle), -::sin(angle), 0.0, 0.0,
		::sin(angle), cos(angle), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}


	}
}

#endif