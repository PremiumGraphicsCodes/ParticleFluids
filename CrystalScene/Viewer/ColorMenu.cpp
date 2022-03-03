#include "ColorMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"
#include "CrystalScene/AppBase/ColorMapView.h"
#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

class ColorMapMenuItem : public MenuItem
{
public:
	ColorMapMenuItem(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
		MenuItem(name),
		control(control)
	{
	}

	void onPushed() override
	{
		control->setWindow(new ColorMapView("ColorMap"));
	}

private:
	ControlPanel* control;
};

ColorMenu::ColorMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
	add(new ColorMapMenuItem(name, model, canvas, control));
}
