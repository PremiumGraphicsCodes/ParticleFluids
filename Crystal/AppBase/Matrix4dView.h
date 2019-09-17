#pragma once

#include "IWindow.h"

#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace UI {

class Matrix4dView : public IWindow
{
public:
	/*
	explicit Matrix4dView(const std::string& name) :
		IWindow(name),
		value(Math::Matrix4dd(1, 0, 0, 0, 1, 0, 0, 0, 1))
	{}
	*/

	Matrix4dView(const std::string& name, const Math::Matrix4dd& value) :
		IWindow(name),
		value(value)
	{}

	void onShow() override;

	void setValue(const Math::Matrix4dd& value) { this->value = value; }

	Math::Matrix4dd getValue() const { return value; }

private:
	Math::Matrix4dd value;
};

	}
}