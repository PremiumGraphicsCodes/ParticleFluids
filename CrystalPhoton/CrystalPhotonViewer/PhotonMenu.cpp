#include "PhotonMenu.h"

#include "CrystalScene/AppBase/imgui.h"
#include "CrystalScene/AppBase/ControlPanel.h"

#include "PCSphereView.h"

#include "PhotonTracerView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PhotonMenu::PhotonMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{
}

void PhotonMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("PCSphere")) {
			control->setWindow(new PCSphereView("PCSphere", world, canvas));
		}
		if (ImGui::MenuItem("PhotonTracer")) {
			control->setWindow(new PhotonTracerView("PhotonTracer", world, canvas));
		}
		ImGui::EndMenu();
	}
}
