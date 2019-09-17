#pragma once

#include "IWindow.h"

#include "Vector3dView.h"

#include "../Math/Box3d.h"

namespace Crystal {
	namespace UI {

class Box3dView : public IWindow
{
public:
	Box3dView(const std::string& name);

	void onShow() override;

	Math::Box3d getValue() const;

private:
	Vector3dView min;
	Vector3dView max;
};

	}
}