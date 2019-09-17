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
	explicit Cone3dView(const std::string& name);

	void onShow() override;

	Math::Cone3d getValue() const;

private:
	Vector3dView center;
	DoubleView radius;
	DoubleView height;
};

	}
}
