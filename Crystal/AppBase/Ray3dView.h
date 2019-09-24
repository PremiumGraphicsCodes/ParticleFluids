#pragma once

#include "IView.h"
#include "Vector3dView.h"
#include "../Math/Ray3d.h"

namespace Crystal {
	namespace UI {

class Ray3dView : public IView
{
public:
	explicit Ray3dView(const std::string& name);

	Math::Ray3d getValue() const;

private:
	Vector3dView origin;
	Vector3dView direction;
};

	}
}