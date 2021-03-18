#pragma once

#include "../../Crystal/Math/Matrix2d.h"
#include "../../Crystal/Math/Matrix3d.h"
#include "../../Crystal/Math/Matrix4d.h"
#include "Eigen/Core"

namespace Crystal {
	namespace Numerics {
		namespace Impl {

class Converter
{
public:
	static Eigen::Matrix2f toEigen(const Math::Matrix2dd& src);

	static Eigen::Matrix3f toEigen(const Math::Matrix3dd& src);

	static Eigen::Matrix4f toEigen(const Math::Matrix4dd& src);

	static Math::Matrix2df fromEigen(const Eigen::Matrix2f& src);

	static Math::Matrix3df fromEigen(const Eigen::Matrix3f& src);

	static Math::Matrix4dd fromEigen(const Eigen::Matrix4d& src);
};
		}
	}
}