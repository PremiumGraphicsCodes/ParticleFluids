#pragma once

#include "IPopupButton.h"

#include "../Math/Cylinder3d.h"

#include "Vector3dView.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class Cylinder3dView : public IWindow
{
public:
	Cylinder3dView(const std::string& name) :
		IWindow(name),
		center("Center", Math::Vector3dd(0,0,0)),
		radius("Radius", 1.0),
		height("Height", 1.0)
	{
	}

	void show() override
	{
		center.show();
		radius.show();
		height.show();
	}

	Math::Cylinder3d getValue() const {
		return Math::Cylinder3d(radius.getValue(), height.getValue(), center.getValue());
	}

private:
	Vector3dView center;
	DoubleView radius;
	DoubleView height;
};

	}
}