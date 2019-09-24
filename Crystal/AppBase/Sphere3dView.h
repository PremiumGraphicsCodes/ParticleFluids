#pragma once

#include "IView.h"
#include "../Math/Sphere3d.h"
#include "Vector3dView.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class Sphere3dView : public IView
{
public:
	Sphere3dView(const std::string& name) :
		IView(name),
		center("Center", Math::Vector3dd(0,0,0)),
		radius("Radius", 1.0)
	{
		add(&center);
		add(&radius);
	}

	Math::Sphere3d getValue() const { return Math::Sphere3d(center.getValue(), radius.getValue()); }

	void setValue(const Math::Sphere3d& value)
	{
		this->center.setValue(value.getCenter());
		this->radius.setValue(value.getRadius());
	}

private:
	Vector3dView center;
	DoubleView radius;
};
	}
}

