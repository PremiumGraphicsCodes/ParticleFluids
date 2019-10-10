#include "LightAddView.h"

#include "../../Crystal/Scene/World.h"
#include "Canvas.h"
#include "../Command/CameraFitCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

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

	CameraFitCommand command;
	command.execute(model);

}
