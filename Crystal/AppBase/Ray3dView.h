#pragma once

#include "IWindow.h"

#include "Vector3dView.h"

#include "../Math/Ray3d.h"

namespace Crystal {
	namespace UI {

class Ray3dView : public IWindow
{
public:
	Ray3dView(const std::string& name) :
		IWindow(name),
		origin("Origin", Math::Vector3dd(0, 0, 0)),
		direction("Direction", Math::Vector3dd(0, 0, 1))
	{
	}

	void show() override
	{
		origin.show();
		direction.show();
	}

	Math::Ray3d getValue() const { return Math::Ray3d(origin.getValue(), direction.getValue()); }

private:
	Vector3dView origin;
	Vector3dView direction;
};

	}
}