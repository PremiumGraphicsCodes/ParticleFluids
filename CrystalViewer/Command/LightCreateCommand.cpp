#include "LightCreateCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string LightCreateCommand::getName()
{
	return "LightCreateCommand";
}

LightCreateCommand::Args::Args() :
	position("Position", Vector3dd(0,0,0)),
	ambient("Ambient", Graphics::ColorRGBAf(0,0,0,0)),
	diffuse("Diffuse", Graphics::ColorRGBAf(0,0,0,0)),
	specular("Specular", Graphics::ColorRGBAf(0, 0, 0, 0)),
	name("name", std::string(""))
{
	add(&position);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&name);
}

LightCreateCommand::Results::Results() :
	newId("NewId", -1)
{
	add(&newId);
}

void LightCreateCommand::execute(World* world)
{
	PointLight l;
	l.setPosition(args.position.getValue());
	l.setAmbient(args.ambient.getValue());
	l.setDiffuse(args.diffuse.getValue());
	l.setSpecular(args.specular.getValue());
	auto scene = world->getObjectFactory()->createLightScene(l, args.name.getValue());
}
