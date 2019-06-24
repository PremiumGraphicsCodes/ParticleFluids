#pragma once

#include "glm.h"

#include <vector>
#include <array>

namespace Crystal {
	namespace Math {

using Matrix2df = glm::mat2;
using Matrix2dd = glm::dmat2;

static Matrix2dd rotationMatrix(double angle)
{
	return Matrix2dd
	(
		::cos(angle), -::sin(angle),
		::sin(angle), ::cos(angle)
	);
}

static bool areSame(const Matrix2dd& lhs, const Matrix2dd& rhs, const double tolerance)
{
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (::fabs(lhs[i][j] - rhs[i][j]) > tolerance) {
				return false;
			}
		}
	}
	return true;
}


	}
}