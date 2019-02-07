#ifndef __CRYSTAL_MATH_MATRIX_3D_H_
#define __CRYSTAL_MATH_MATRIX_3D_H_

#include "Tolerance.h"
#include "../ThirdParty/glm-0.9.8.5/glm/glm.hpp"

#include <vector>
#include <array>

namespace Crystal {
	namespace Math {

using Matrix3df = glm::mat3;
using Matrix3dd = glm::dmat3;

static Matrix3dd rotationMatrixX(double angle)
{
	return Matrix3dd
	(
		1.0, 0.0, 0.0,
		0.0, ::cos(angle), -::sin(angle),
		0.0, ::sin(angle), ::cos(angle)
	);
}

static Matrix3dd rotationMatrixY(double angle)
{
	return Matrix3dd
	(
		::cos(angle), 0.0, ::sin(angle),
		0.0, 1.0, 0.0,
		-::sin(angle), 0.0, ::cos(angle)
	);
}

static Matrix3dd rotationMatrixZ(double angle)
{
	return Matrix3dd
	(
		::cos(angle), -::sin(angle), 0.0,
		::sin(angle), cos(angle), 0.0,
		0.0, 0.0, 1.0
	);
}

static bool AreSame(const Matrix3dd& lhs, const Matrix3dd& rhs, const double tolerance)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (::fabs(lhs[i][j] - rhs[i][j]) > tolerance) {
				return false;
			}
		}
	}
	return true;
}

	}
}

#endif