#include "Button.h"
#include "imgui.h"

using namespace Crystal::UI;

void Button::show()
{
	auto str = name.c_str();
	if (ImGui::Button(str)) {
		func();
	}
}
