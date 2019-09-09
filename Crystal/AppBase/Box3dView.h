#pragma once

#include "IWindow.h"

#include "Vector3dView.h"

#include "../Math/Box3d.h"

namespace Crystal {
	namespace UI {

class Box3dView : public IWindow
{
public:
	Box3dView(const std::string& name) :
		IWindow(name),
		min("Min", Math::Vector3dd(0,0,0)),
		max("Max", Math::Vector3dd(1,1,1))
	{
	}

	void onShow() override
	{
		min.show();
		max.show();
	}

	Math::Box3d getValue() const { return Math::Box3d(min.getValue(), max.getValue()); }

private:
	Vector3dView min;
	Vector3dView max;

};
	}
}