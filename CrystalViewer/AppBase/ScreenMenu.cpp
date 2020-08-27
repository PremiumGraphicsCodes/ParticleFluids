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
			model->getRenderer()->setRenderTarget(Crystal::Scene::RenderTarget::Shaded);
		}
		if (ImGui::MenuItem("ParentId")) {
			model->getRenderer()->setRenderTarget(Crystal::Scene::RenderTarget::ParentId);
		}
		ImGui::EndMenu();
	}
}
