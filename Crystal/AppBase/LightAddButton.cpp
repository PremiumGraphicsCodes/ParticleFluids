#include "LightAddButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

LightAddButton::LightAddButton(Repository* model, Canvas* canvas)
	:
	IPopupButton("Light", model, canvas),
	position("Position", Vector3dd(0, 0, 0)),
	ambient("Ambient", glm::vec4(0, 0, 0, 0)),
	diffuse("Diffuse", glm::vec4(0, 0, 0, 0)),
	specular("Specular", glm::vec4(0, 0, 0, 0)),
	name("Name", "Light1")
{
}

void LightAddButton::onShow()
{
	position.show();
	ambient.show();
	diffuse.show();
	specular.show();
	name.show();
}

void LightAddButton::onOk()
{
	auto l = new PointLight();
	l->setPosition(position.getValue());
	l->setAmbient(ambient.getValue());
	l->setDiffuse(diffuse.getValue());
	l->setSpecular(specular.getValue());
	getModel()->getAppearances()->getLights()->add(l, name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void LightAddButton::onCancel()
{
}
