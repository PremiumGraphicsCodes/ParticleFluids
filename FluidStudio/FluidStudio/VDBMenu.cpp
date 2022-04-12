#include "VDBMenu.h"

#include "ToVolumeView.h"

#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

VDBMenu::VDBMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{
	add(new MenuItem("ToVolume", [world, canvas, control] {
		control->setWindow(new ToVolumeView("ToVolume", world, canvas));
		}));
}