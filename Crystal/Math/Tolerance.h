#ifndef __CRYSTAL_MATH_TOLERANCE_H__
#define __CRYSTAL_MATH_TOLERANCE_H__

#include <cmath>

namespace Crystal {
	namespace Math {

template<typename T>
class Tolerance
{

};

template<>
class Tolerance < double > final
{
public:
	static double getLooseTolerance() {
		return 1.0e-9;
	}

	static double getStrictTolerance() {
		return 1.0e-18;
	}

	static bool isEqual(const double x, const double y, const double tolerance) { return ::fabs(x - y) < tolerance; }

	static double getHalfPI() { return 0.5 * getPI(); }

	static double getPI() { return 3.141592653589793238462643383279; }

	static double getTwoPI() { return 2.0 * getPI(); }
};
	}
}

#endif