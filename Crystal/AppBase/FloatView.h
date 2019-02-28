#pragma once

#include "IWindow.h"
#include "imgui.h"

namespace Crystal {
	namespace UI {

class FloatView : public IWindow
{
public:
	FloatView(const std::string& name, const float value) :
		IWindow(name),
		value(value)
	{}

	void show() override {
		ImGui::InputFloat(name.c_str(), &value);
	}

	float getValue() const { return value; }

private:
	float value;
};

	}
}