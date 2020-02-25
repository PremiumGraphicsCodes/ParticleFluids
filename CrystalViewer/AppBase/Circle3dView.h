#pragma once

#include "IView.h"

#include "Vector3dView.h"

#include "../../Crystal/Math/Circle3d.h"

namespace Crystal {
	namespace UI {

class Circle3dView : public IView
{
public:
	explicit Circle3dView(const std::string& name);

	Math::Circle3d getValue() const;

	void setValue(const Math::Circle3d& value);

private:
	Vector3dView centerView;
	Vector3dView uvecView;
	Vector3dView vvecView;
};

	}
}