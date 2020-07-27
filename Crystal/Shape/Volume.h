#pragma once

#include "IShape.h"

#include "Particle.h"

#include "../Math/Box3d.h"

#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

class Volume : public IShape
{
public:
	Volume() {}

	~Volume() {
		//clear();
	}

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	Math::Box3d getBoundingBox() const override { box; }

private:
	Math::Box3d box;
};

	}
}
