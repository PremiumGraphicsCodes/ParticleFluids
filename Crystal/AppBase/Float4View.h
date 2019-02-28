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
		IWindow(name),
		value(0,0,0,0)
	{}

	void show() override {
		ImGui::InputFloat4(name.c_str(), &value[0]);
	}

	glm::vec4 getValue() const { return value; }

private:
	glm::vec4 value;
};

	}
}