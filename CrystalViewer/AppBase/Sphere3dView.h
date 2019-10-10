#pragma once

#include "IView.h"
#include "../../Crystal/Math/Sphere3d.h"
#include "Vector3dView.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class Sphere3dView : public IView
{
public:
	explicit Sphere3dView(const std::string& name);

	Math::Sphere3d getValue() const;

	void setValue(const Math::Sphere3d& value);

private:
	Vector3dView center;
	DoubleView radius;
};
	}
}

