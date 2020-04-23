#include "ScreenMenu.h"
#include "imgui.h"
#include "../../Crystal/Scene/World.h"
#include "Canvas.h"

using namespace Crystal::UI;

void ScreenMenu::onShow()
{
	auto model = getWorld();
	auto canvas = getCanvas();

	//const auto& textures = model->getShaders()->getTextures()->getTextures();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("OnScreen")) {
			model->getRenderer()->setShowOffScreen(false);
		}
		if (ImGui::MenuItem("ParentId")) {
			model->getRenderer()->setShowOffScreen(true);
		}
		ImGui::EndMenu();
	}
}
