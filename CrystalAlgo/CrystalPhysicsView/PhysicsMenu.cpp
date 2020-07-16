#include "PhysicsMenu.h"

#include "KFFluidSimulationView.h"
#include "PBFluidSimulationView.h"
#include "DFSPHFluidSimulationView.h"

#include "../../CrystalViewer/AppBase/imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PhysicsMenu::PhysicsMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void PhysicsMenu::onShow()
{
	if (ImGui::BeginMenu("Physics")) {
		if (ImGui::MenuItem("KFFluid")) {
			control->setWindow(new KFFluidSimulationView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("PBFluid")) {
			control->setWindow(new PBFluidSimulationView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("DFSPHFluid")) {
			control->setWindow(new DFSPHFluidSimulationView(getWorld(), getCanvas()));
		}
		ImGui::EndMenu();
	}
}
