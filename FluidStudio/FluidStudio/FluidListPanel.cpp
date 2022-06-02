#include "FluidListPanel.h"

#include "CrystalScene/Scene/World.h"

#include "CrystalScene/AppBase/imgui.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
#include "FluidView.h"
#include "EmitterView.h"
#include "SolverView.h"

using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;
using namespace PG::FS;

FluidListPanel::FluidListPanel(const std::string& name, World* model, Canvas* canvas, IPanel* control, SolverModel* solver) :
	IPanel(name, model, canvas),
	control(control),
	solver(solver)
{
}

void FluidListPanel::onShow()
{
	ImGui::Begin("FluidList");
	const auto& fluids = solver->getFluids();
	for (const auto& f : fluids) {
		const auto str = f->name.c_str();
		if (ImGui::Button(str)) {
			auto fluidView = new FluidView("Fluid", getWorld(), getCanvas());
			fluidView->setValue(f.get());
			control->clear();
			control->add(fluidView);
		}

	}
	const auto& emitters = solver->getEmitters();
	for (const auto& e : emitters) {
		const auto str = e->name.c_str();
		if (ImGui::Button(str)) {
			auto fluidView = new EmitterView("Emitter", getWorld(), getCanvas());
			fluidView->setValue(e.get());
			control->clear();
			control->add(fluidView);
		}

	}
	//show(getWorld()->getScenes());
	ImGui::End();
}
