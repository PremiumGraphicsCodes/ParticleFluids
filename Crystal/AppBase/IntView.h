#pragma once

#include "IWindow.h"
#include "imgui.h"

namespace Crystal {
	namespace UI {

class IntView : public IWindow
{
public:
	explicit IntView(const std::string& name) :
		IWindow(name),
		value(0)
	{}

	IntView(const std::string& name, const int value) :
		IWindow(name),
		value(value)
	{}

	void show() override {
		ImGui::InputInt(name.c_str(), &value);
	}

	int getValue() const { return value; }

	void setValue(const int value) { this->value = value; }

private:
	int value;
};

	}
}