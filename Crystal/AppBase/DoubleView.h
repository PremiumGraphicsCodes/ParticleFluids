#pragma once

#include "IWindow.h"
#include "imgui.h"

namespace Crystal {
	namespace UI {

class DoubleView : public IWindow
{
public:
	DoubleView(const std::string& name, const double value) :
		IWindow(name),
		value(value)
	{}

	void show() override {
		ImGui::InputDouble(name.c_str(), &value);
	}

	double getValue() const { return value; }

	void setValue(const double value) { this->value = value; }

private:
	double value;
};

	}
}