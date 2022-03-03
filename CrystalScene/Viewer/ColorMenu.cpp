#include "ColorMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"
#include "CrystalScene/AppBase/ColorMapView.h"
#include "CrystalScene/AppBase/IMenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

class ControlChangeMenuItem : public IMenuItem
{
public:
	ControlChangeMenuItem(const std::string& name, ControlPanel* control, IWindow* window) :
		IMenuItem(name),
		control(control),
		window(window)
	{}

protected:
	void onPushed() override
	{
		control->setWindow(window);
	}

private:
	ControlPanel* control;
	IWindow* window;
};

/*
class ColorMapMenuItem : public IMenuItem
{
public:
	ColorMapMenuItem(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
		IMenuItem(name),
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
*/

ColorMenu::ColorMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{	 
	add(new ControlChangeMenuItem(name, control, new ColorMapView("ColorMap")));
}
