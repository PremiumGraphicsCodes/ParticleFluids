#include "LightAddView.h"

#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

LightAddView::LightAddView(const std::string& name, RootScene* model, Canvas* canvas) :
	IPanel(name, model, canvas),
	light("LAdd"),
	name("Name", "Light01"),
	ok("Ok")
{
	ok.setFunction([=]() { onOk(); });
}

void LightAddView::show()
{
	light.show();
	name.show();
	ok.show();
}

void LightAddView::onOk()
{
	getRepository()->getObjects()->addScene( getRepository()->getObjectFactory()->createLightScene(light.getValue(), name.getValue()) );
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
