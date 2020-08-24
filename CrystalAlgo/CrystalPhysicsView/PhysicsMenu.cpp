#include "PhysicsMenu.h"

#include "CSPHFluidSimulationView.h"
#include "KFFluidSimulationView.h"
#include "PBSPHFluidSimulationView.h"
#include "DFSPHFluidSimulationView.h"
#include "MeshToParticleView.h"

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
		if (ImGui::MenuItem("CSPH")) {
			control->setWindow(new CSPHFluidSimulationView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("KFFluid")) {
			control->setWindow(new KFFluidSimulationView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("PBSPHFluid")) {
			control->setWindow(new PBSPHFluidSimulationView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("DFSPHFluid")) {
			control->setWindow(new DFSPHFluidSimulationView(getWorld(), getCanvas()));
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Tools")) {
		if (ImGui::MenuItem("MeshToParticle")) {
			control->setWindow(new MeshToParticleView("MeshToParticle", getWorld(), getCanvas()));
		}
		ImGui::EndMenu();
	}
}
