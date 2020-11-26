#pragma once

#include "../Math/ISolid3d.h"

#include "IShape.h"
#include <memory>

namespace Crystal {
	namespace Shape {

class Solid : public IShape
{
public:
	explicit Solid(std::unique_ptr<Math::ISolid3d> shape);

	~Solid() {};

	void move(const Math::Vector3dd& v) {}

	void transform(const Math::Matrix3dd& m) { matrix *= Math::Matrix4dd(m); }

	void transform(const Math::Matrix4dd& m) { matrix *= m; }

	Math::Box3d getBoundingBox();

private:
	std::unique_ptr<Math::ISolid3d> shape;
	Math::Matrix4dd matrix;
};

	}
}