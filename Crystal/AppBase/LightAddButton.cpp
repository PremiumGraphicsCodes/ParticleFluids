#include "LightAddButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

LightAddButton::LightAddButton(Repository* model, Canvas* canvas) :
	IPopupButton("Light", model, canvas),
	light("LightAdd"),
	name("Name", "Light01")
{
}

void LightAddButton::onShow()
{
}

void LightAddButton::onOk()
{
	getModel()->getAppearances()->getLights()->add(light.getValue(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void LightAddButton::onCancel()
{
}
