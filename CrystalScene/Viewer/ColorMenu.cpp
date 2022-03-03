#include "ColorMenu.h"
#include "CrystalScene/AppBase/ControlChangeMenuItem.h"
#include "CrystalScene/AppBase/ColorMapView.h"
#include "CrystalScene/AppBase/IMenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;


ColorMenu::ColorMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{	 
	add(new ControlChangeMenuItem(name, control, new ColorMapView("ColorMap")));
}
