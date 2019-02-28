#pragma once

#include "IWindow.h"

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace UI {

class Vector3dView : public IWindow
{
public:
	Vector3dView(const std::string& name, const Math::Vector3dd& value) :
		IWindow(name),
		value(value)
	{}

	void show() override;

	Math::Vector3dd getValue() const { return value; }

private:
	Math::Vector3df value;
};

	}
}