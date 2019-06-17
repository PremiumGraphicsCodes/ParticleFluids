#ifndef __CRYSTAL_MATH_MATRIX_4D_H__
#define __CRYSTAL_MATH_MATRIX_4D_H__

#include <cassert>
#include <array>
#include "glm.h"

namespace Crystal {
	namespace Math {

using Matrix4df = glm::mat4;
using Matrix4dd = glm::dmat4;

static Matrix4dd operator*(const Matrix4dd& lhs, const Matrix4dd& rhs)
{
	Matrix4dd result(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}
	return result;
}

	}
}

#endif