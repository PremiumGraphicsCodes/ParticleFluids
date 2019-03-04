#pragma once

#include "IWindow.h"

#include "Vector3dView.h"

#include "../Math/Plane3d.h"

namespace Crystal {
	namespace UI {

class Plane3dView : public IWindow
{
public:
	Plane3dView(const std::string& name) :
		IWindow(name),
		origin("Origin", Math::Vector3dd(0,0,0)),
		normal("Normal", Math::Vector3dd(0,0,1))
	{
	}

	void show() override
	{
		origin.show();
		normal.show();
	}

	Math::Plane3d getValue() const { return Math::Plane3d(origin.getValue(), normal.getValue()); }

private:
	Vector3dView origin;
	Vector3dView normal;
};

	}
}