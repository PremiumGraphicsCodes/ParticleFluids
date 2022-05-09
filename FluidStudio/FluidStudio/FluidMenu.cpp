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
		model->getSolver()->addFluid(world);
		}));

	add(new MenuItem("Emitter", [world, canvas, control, model] {
		model->getSolver()->addEmitter(world);
		//control->setWindow(new EmitterView("Emitter", world, canvas));
	}));
}