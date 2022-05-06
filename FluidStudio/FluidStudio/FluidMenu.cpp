#include "FluidMenu.h"

#include "SolverView.h"
#include "FluidView.h"
#include "EmitterView.h"

#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

FluidMenu::FluidMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control, MainModel* model) :
	IMenu(name, world, canvas),
	control(control)
{
	add(new MenuItem("Fluid", [world, canvas, control, model] {
		/*
		auto fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");
		fluidScene->getPresenter()->createView(world->getRenderer());
		world->getScenes()->addScene(fluidScene);
		model->addFluidScene(fluidScene);
		*/
		}));

	add(new MenuItem("Emitter", [world, canvas, control, model] {
		//control->setWindow(new EmitterView("Emitter", world, canvas, model));
		}));

}