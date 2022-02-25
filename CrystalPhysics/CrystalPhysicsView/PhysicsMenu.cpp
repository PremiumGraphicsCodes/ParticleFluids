#include "PhysicsMenu.h"

#include "CSPHFluidSimulationView.h"
#include "MVPFluidSimulationView.h"
#include "PBSPHFluidSimulationView.h"
#include "DFSPHFluidSimulationView.h"
#include "MPSFluidSimulationView.h"
#include "SPHFlameSimulationView.h"

#include "MeshBoundaryView.h"
#include "SPHSurfaceBuilderView.h"
#include "MVPSurfaceBuilderView.h"
#include "MVPSamplerView.h"

#include "CrystalScene/AppBase/imgui.h"

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
			control->setWindow(new CSPHFluidSimulationView("CSPHFluid", world, canvas));
		}
		if (ImGui::MenuItem("MVPFluid")) {
			control->setWindow(new MVPFluidSimulationView("MVPFluid", world, canvas));
		}
		if (ImGui::MenuItem("MVPSampler")) {
			control->setWindow(new MVPSamplerView("MVPSampler",world, canvas));
		}
		if (ImGui::MenuItem("PBSPHFluid")) {
			control->setWindow(new PBSPHFluidSimulationView("PBFluid", world, canvas));
		}
		if (ImGui::MenuItem("DFSPHFluid")) {
			control->setWindow(new DFSPHFluidSimulationView("DFSPH", world, canvas));
		}
		if (ImGui::MenuItem("MPSFluid")) {
			control->setWindow(new MPSFluidSimulationView("MPSFluid",world, canvas));
		}
		if (ImGui::MenuItem("SPHFlame")) {
			control->setWindow(new SPHFlameSimulationView("SPHFlame",world, canvas));
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Boundary")) {
		if (ImGui::MenuItem("MeshBoundary")) {
			control->setWindow(new MeshBoundaryView("Mesh", world, canvas));
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("SPHSurface")) {
		if(ImGui::MenuItem("SPHSurface")) {
			control->setWindow(new SPHSurfaceBuilderView("SPHSurface", world, canvas));
		}
		if (ImGui::MenuItem("MVPSurface")) {
			control->setWindow(new MVPSurfaceBuilderView("MVPSurface", world, canvas));
		}
		ImGui::EndMenu();
	}
}