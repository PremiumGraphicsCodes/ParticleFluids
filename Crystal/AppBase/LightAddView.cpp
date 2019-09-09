#include "LightAddView.h"

#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

LightAddView::LightAddView(const std::string& name, World* model, Canvas* canvas) :
	IPanel(name, model, canvas),
	light("LAdd"),
	name("Name", "Light01"),
	ok("Ok")
{
	ok.setFunction([=]() { onOk(); });
}

void LightAddView::onShow()
{
	light.show();
	name.show();
	ok.show();
}

void LightAddView::onOk()
{
	getWorld()->getObjects()->addScene( getWorld()->getObjectFactory()->createLightScene(light.getValue(), name.getValue()) );
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
