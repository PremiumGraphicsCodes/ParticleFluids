#include "LightSetCommand.h"

#include "Public/LightSetLabels.h"

#include "../../Crystal/Scene/LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string LightSetCommand::getName()
{
	return LightSetLabels::CommandNameLabel;
}

LightSetCommand::Args::Args() :
	id(LightSetLabels::IdLabel, -1),
	position(LightSetLabels::PositionLabel, Vector3dd(0, 0, 0)),
	ambient(LightSetLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(LightSetLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(LightSetLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	name(LightSetLabels::NameLabel, std::string(""))
{
	add(&id);
	add(&position);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&name);
}

void LightSetCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<LightScene*>(args.id.getValue());
	auto l = scene->getLight();
	l.setPosition(args.position.getValue());
	l.setAmbient(args.ambient.getValue());
	l.setDiffuse(args.diffuse.getValue());
	l.setSpecular(args.specular.getValue());
	scene->setLight(l);
	scene->setName(args.name.getValue());
}
