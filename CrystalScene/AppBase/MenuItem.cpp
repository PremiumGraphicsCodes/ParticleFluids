#include "MenuItem.h"
#include "imgui.h"

using namespace Crystal::UI;

void MenuItem::onShow()
{
	auto str = name.c_str();
	if (ImGui::MenuItem(str)) {
		onPushed();
	}
}
