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
	explicit Cylinder3dView(const std::string& name);

	void onShow() override;

	Math::Cylinder3d getValue() const;

	void setValue(const Math::Cylinder3d& value);

private:
	Vector3dView center;
	DoubleView radius;
	DoubleView height;
};

	}
}