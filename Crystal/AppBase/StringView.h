#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "imgui_stdlib.h"

namespace Crystal {
	namespace UI {

class StringView : public IWindow
{
public:
	StringView(const std::string& name, const std::string& value) :
		IWindow(name),
		value(value)
	{}

	void show() override {
		ImGui::InputText(name.c_str(), &value);
	}

	std::string getValue() const { return std::string(value); }

private:
	std::string value;
};

	}
}