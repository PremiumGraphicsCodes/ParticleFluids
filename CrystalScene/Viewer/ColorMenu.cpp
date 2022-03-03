#include "ColorMenu.h"
#include "../../CrystalScene/AppBase/imgui.h"
#include "../../CrystalScene/AppBase/ControlPanel.h"
#include "../../CrystalScene/AppBase/ColorMapView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

class ColorMapMenuItem : public IWindow
{
public:
	ColorMapMenuItem(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
		IWindow(name),
		control(control)
	{
	}

	void onShow() override
	{
		if (ImGui::MenuItem("ColorMap")) {
			control->setWindow(new ColorMapView("CMap"));
		}
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
