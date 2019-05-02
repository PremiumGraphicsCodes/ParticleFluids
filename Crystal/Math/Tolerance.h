#ifndef __CRYSTAL_MATH_TOLERANCE_H__
#define __CRYSTAL_MATH_TOLERANCE_H__

#include <cmath>

namespace Crystal {
	namespace Math {

static const double PI = 3.141592653589793238462643383279;

static bool isEqual(const double x, const double y, const double tolerance) { return ::fabs(x - y) < tolerance; }

	}
}

#endif