#include "AppearanceMenu.h"
#include "imgui.h"
#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"
#include "ControlPanel.h"

#include "LightAddView.h"
#include "MaterialAddView.h"
#include "TextureAddView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

void AppearanceMenu::show()
{
	auto model = getModel();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {

		if (ImGui::MenuItem("Light")) {
			control->setWindow(new LightAddView("Light", getModel(), canvas));
		}
		if (ImGui::MenuItem("Material")) {
			control->setWindow(new MaterialAddView("Material", getModel(), canvas));
		}
		if (ImGui::MenuItem("Texture")) {
			control->setWindow(new TextureAddView("Texture", getModel(), canvas));
		}


		ImGui::EndMenu();
	}
}
