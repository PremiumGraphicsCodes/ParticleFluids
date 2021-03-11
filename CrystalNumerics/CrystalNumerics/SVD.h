#pragma once

#include "../../Crystal/Math/Matrix2d.h"
#include "../../Crystal/Math/Matrix3d.h"
#include "../../Crystal/Math/Matrix4d.h"

namespace Crystal {
	namespace Numerics {

class SVD
{
public:
	void calculate(const Math::Matrix2dd& lhs);

	void calculate(const Math::Matrix3dd& lhs);

	void calculate(const Math::Matrix4dd& lhs);
};
	}
}