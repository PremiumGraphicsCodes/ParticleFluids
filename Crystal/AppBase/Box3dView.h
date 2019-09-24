#pragma once

#include "IView.h"

#include "Vector3dView.h"

#include "../Math/Box3d.h"

namespace Crystal {
	namespace UI {

class Box3dView : public IView
{
public:
	Box3dView(const std::string& name);

	Math::Box3d getValue() const;

	void setValue(const Math::Box3d& value);

private:
	Vector3dView minView;
	Vector3dView maxView;
};

	}
}