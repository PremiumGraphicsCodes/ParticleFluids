#include "LightGetCommand.h"

#include "Public/LightGetLabels.h"
#include "../../Crystal/Scene/LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string LightGetCommand::getName()
{
	return LightGetLabels::CommandNameLabel;
}

LightGetCommand::Args::Args() :
	id(LightGetLabels::IdLabel, -1)
{
	add(&id);
}

LightGetCommand::Results::Results() :
	position(LightGetLabels::PositionLabel, Vector3dd(0,0,0)),
	ambient(LightGetLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(LightGetLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(LightGetLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	name(LightGetLabels::NameLabel, std::string(""))
{
	add(&position);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&name);
}

void LightGetCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<LightScene*>(args.id.getValue());
	if (scene == nullptr) {
		return;
	}
	auto m = scene->getLight();
	results.position.setValue(m.getPosition());
	results.ambient.setValue(Graphics::ColorRGBAf(m.getAmbient()));
	results.diffuse.setValue(Graphics::ColorRGBAf(m.getDiffuse()));
	results.specular.setValue(Graphics::ColorRGBAf(m.getSpecular()));
	results.name.setValue(scene->getName());
}