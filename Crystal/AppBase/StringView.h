#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "imgui_stdlib.h"

namespace Crystal {
	namespace UI {

class StringView : public IWindow
{
public:
	explicit StringView(const std::string& name) :
		IWindow(name),
		value("")
	{}

	StringView(const std::string& name, const std::string& value) :
		IWindow(name),
		value(value)
	{}

	void onShow() override
	{
		ImGui::InputText(name.c_str(), &value);
	}

	std::string getValue() const { return value; }

	void setValue(const std::string& value) { this->value = value; }

private:
	std::string value;
};

	}
}