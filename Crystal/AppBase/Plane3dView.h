#pragma once

#include "IWindow.h"

#include "Vector3dView.h"

#include "../Math/Plane3d.h"

namespace Crystal {
	namespace UI {

class Plane3dView : public IWindow
{
public:
	explicit Plane3dView(const std::string& name);

	void onShow() override;

	Math::Plane3d getValue() const;

private:
	Vector3dView origin;
	Vector3dView normal;
};

	}
}