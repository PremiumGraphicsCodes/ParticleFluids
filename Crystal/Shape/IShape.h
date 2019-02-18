#pragma once

#include "../Util/UnCopyable.h"
#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"

namespace Crystal {
	namespace Shape {

class IShape : private UnCopyable
{
public:
	IShape() {}

	virtual ~IShape() {};

	virtual void move(const Math::Vector3dd& v) = 0;

	virtual void transform(const Math::Matrix3dd& m) = 0;
};
	}
}