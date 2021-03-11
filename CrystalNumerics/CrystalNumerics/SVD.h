#pragma once

#include "../../Crystal/Math/Matrix3d.h"

namespace Crystal {
	namespace Numerics {

class SVD
{
public:
	void calculate(const Math::Matrix3dd& lhs, const Math::Matrix3dd& rhs);
};
	}
}