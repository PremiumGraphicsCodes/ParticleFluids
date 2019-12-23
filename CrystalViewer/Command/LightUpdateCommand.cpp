#include "LightUpdateCommand.h"

#include "Public/LightUpdateLabels.h"

#include "../../Crystal/Scene/LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string LightUpdateCommand::getName()
{
	return LightUpdateLabels::CommandNameLabel;
}

LightUpdateCommand::Args::Args() :
	id(LightUpdateLabels::IdLabel, -1),
	position(LightUpdateLabels::PositionLabel, Vector3dd(0, 0, 0)),
	ambient(LightUpdateLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(LightUpdateLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(LightUpdateLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	name(LightUpdateLabels::NameLabel, std::string(""))
{
	add(&id);
	add(&position);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&name);
}

void LightUpdateCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<LightScene*>(args.id.getValue());
	PointLight l = scene->getLight();
	l.setPosition(args.position.getValue());
	l.setAmbient(args.ambient.getValue());
	l.setDiffuse(args.diffuse.getValue());
	l.setSpecular(args.specular.getValue());
	scene->setLight(l);
	scene->setName(args.name.getValue());
}
