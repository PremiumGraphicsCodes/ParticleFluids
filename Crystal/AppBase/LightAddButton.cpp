#include "LightAddButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

LightAddButton::LightAddButton(const std::string& name, Repository* model, Canvas* canvas) :
	IPopupButton(name, model, canvas),
	light("Light"),
	name("Name", "Light01")
{
}

void LightAddButton::onShow()
{
	light.show();
	name.show();
}

void LightAddButton::onOk()
{
	getModel()->getAppearances()->getLights()->add(light.getValue().clone(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void LightAddButton::onCancel()
{
}
