#include "ScreenMenu.h"
#include "imgui.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

using namespace Crystal::UI;

void ScreenMenu::show()
{
	auto model = getModel();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("OnScreen")) {
			canvas->getRenderer()->setShowOffScreen(false);
		}
		if (ImGui::MenuItem("OffScreen")) {
			canvas->getRenderer()->setShowOffScreen(true);
		}

		ImGui::EndMenu();
	}
}
