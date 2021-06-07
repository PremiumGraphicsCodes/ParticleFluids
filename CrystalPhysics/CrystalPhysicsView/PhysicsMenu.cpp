#include "PhysicsMenu.h"

#include "CSPHFluidSimulationView.h"
#include "KFFluidSimulationView.h"
#include "PBSPHFluidSimulationView.h"
#include "DFSPHFluidSimulationView.h"
#include "SPHFlameSimulationView.h"

#include "MeshBoundaryView.h"
#include "SPHSurfaceBuilderView.h"

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
	auto world =  getWorld();
	auto canvas = getCanvas();

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
		if (ImGui::MenuItem("SPHFlame")) {
			control->setWindow(new SPHFlameSimulationView(world, canvas));
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Boundary")) {
		if (ImGui::MenuItem("MeshBoundary")) {
			control->setWindow(new MeshBoundaryView("Mesh", getWorld(), getCanvas()));
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("SPHSurface")) {
		if(ImGui::MenuItem("SPHSurface")) {
			control->setWindow(new SPHSurfaceBuilderView("SPHSurface", getWorld(), getCanvas()));
		}
		ImGui::EndMenu();
	}
}
