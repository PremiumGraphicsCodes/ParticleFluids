#include "ScreenMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::UI;

void ScreenMenu::onShow()
{
	/*
	auto model = getModel();
	auto canvas = getCanvas();

	const auto& textures = model->getShaders()->getTextures()->getTextures();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		auto mask = canvas->getMask();

		for (const auto& t : textures) {
			const auto str = t->getName();
			const auto c_str = str.c_str();
			if (ImGui::MenuItem(c_str)) {
				model->getShaders()->getTextures()->setOnScreenTexture(t);
			}
		}

		ImGui::EndMenu();
	}
	*/
}
