#include "LightAddView.h"

#include "../UI/Repository.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

LightAddView::LightAddView(const std::string& name, Repository* model, Canvas* canvas) :
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
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
