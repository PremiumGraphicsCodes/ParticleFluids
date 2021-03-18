#pragma once

#include "../../Crystal/Math/Vector2d.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Matrix2d.h"
#include "../../Crystal/Math/Matrix3d.h"
#include "../../Crystal/Math/Matrix4d.h"

namespace Crystal {
	namespace Numerics {

class SVD
{
public:
	struct SVD2dResult
	{
		bool isOk;
		Math::Vector2dd eigenValues;
		std::array<Math::Vector2dd,2> eigenVectors;
	};

	SVD2dResult calculate(const Math::Matrix2dd& lhs);

	Math::Vector3dd calculate(const Math::Matrix3dd& lhs);

	void calculate(const Math::Matrix4dd& lhs);

private:
	//std::vector<std::vector
};
	}
}