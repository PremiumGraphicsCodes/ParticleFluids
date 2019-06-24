#pragma once

#include "IWindow.h"
#include "imgui.h"

namespace Crystal {
	namespace UI {

class BoolView : public IWindow
{
public:
	BoolView(const std::string& name, const bool value) :
		IWindow(name),
		value(value)
	{}

	void show() override {
		ImGui::Checkbox(name.c_str(), &value);
	}

	bool getValue() const { return value; }

	void setValue(const bool value) { this->value = value; }

private:
	bool value;
};

	}
}