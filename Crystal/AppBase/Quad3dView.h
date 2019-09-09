#pragma once

#include "IWindow.h"

#include "Vector3dView.h"

#include "../Math/Quad3d.h"

namespace Crystal {
	namespace UI {

class Quad3dView : public IWindow
{
public:
	Quad3dView(const std::string& name) :
		IWindow(name),
		origin("Origin", Math::Vector3dd(0, 0, 0)),
		uvec("UVec", Math::Vector3dd(1, 0, 0)),
		vvec("VVec", Math::Vector3dd(0, 1, 0))
	{
	}

	void onShow() override
	{
		origin.show();
		uvec.show();
		vvec.show();
	}

	Math::Quad3d getValue() const { return Math::Quad3d(origin.getValue(), uvec.getValue(), vvec.getValue()); }

private:
	Vector3dView origin;
	Vector3dView uvec;
	Vector3dView vvec;
};

	}
}