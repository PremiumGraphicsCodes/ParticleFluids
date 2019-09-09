#pragma once

#include "IWindow.h"

#include "imgui.h"
#include <array>

namespace Crystal {
	namespace UI {

class Float4View : public IWindow
{
public:
	explicit Float4View(const std::string& name) :
		IWindow(name)
	{}

	Float4View(const std::string& name, const glm::vec4& value) :
		IWindow(name),
		value(value)
	{}

	void onShow() override
	{
		ImGui::InputFloat4(name.c_str(), &value[0]);
	}

	glm::vec4 getValue() const { return value; }

	void setValue(const glm::vec4& value) { this->value = value; }

private:
	glm::vec4 value;
};

	}
}