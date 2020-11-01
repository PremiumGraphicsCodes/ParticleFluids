#include "SimulationMenu.h"

#include "FluidSimulationView.h"

#include "../../CrystalViewer/AppBase/imgui.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;

SimulationMenu::SimulationMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void SimulationMenu::onShow()
{
	auto world = getWorld();

	const auto& n = name.c_str();
	if (ImGui::BeginMenu(n)) {
		if (ImGui::MenuItem("Simulation")) {
			auto view = new FluidSimulationView(getWorld(), getCanvas());
			control->setWindow(view);
		}

		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
