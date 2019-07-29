#pragma once

#include "IWindow.h"

#include "../Math/Matrix3d.h"

namespace Crystal {
	namespace UI {

class Matrix3dView : public IWindow
{
public:
	explicit Matrix3dView(const std::string& name) :
		IWindow(name)
	{}

	Matrix3dView(const std::string& name, const Math::Matrix3dd& value) :
		IWindow(name),
		value(value)
	{}

	void show() override;

	void setValue(const Math::Matrix3dd& value) { this->value = value; }

	Math::Matrix3dd getValue() const { return value; }

private:
	Math::Matrix3dd value;
};

	}
}