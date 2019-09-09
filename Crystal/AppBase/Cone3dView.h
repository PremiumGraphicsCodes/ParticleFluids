#pragma once

#include "IWindow.h"

#include "../Math/Vector3d.h"
#include "../Math/Cone3d.h"

#include "Vector3dView.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class Cone3dView : public IWindow
{
public:
	explicit Cone3dView(const std::string& name) :
		IWindow(name),
		center("Bottom", Math::Vector3dd(0,0,0)),
		radius("Radius", 1.0),
		height("Height", 1.0)
	{
	}

	void onShow() override
	{
		center.show();
		radius.show();
		height.show();
	}

	Math::Cone3d getValue() const { return Math::Cone3d(center.getValue(), radius.getValue(), height.getValue()); }

private:
	Vector3dView center;
	DoubleView radius;
	DoubleView height;
};

	}
}
