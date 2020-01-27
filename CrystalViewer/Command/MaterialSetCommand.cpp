#include "MaterialSetCommand.h"

#include "Public/MaterialSetLabels.h"
#include "../../Crystal/Scene/MaterialScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string MaterialSetCommand::getName()
{
	return MaterialSetLabels::CommandNameLabel;
}

MaterialSetCommand::Args::Args() :
	id(MaterialSetLabels::IdLabel, -1),
	ambient(MaterialSetLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(MaterialSetLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(MaterialSetLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	shininess(MaterialSetLabels::ShininessLabel, 1.0f),
	//textureName(MaterialSetLabels::TextureNameLabel, std::string("")),
	name(MaterialSetLabels::NameLabel, std::string(""))
{
	add(&id);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	//add(&textureName);
	add(&name);
}

bool MaterialSetCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<MaterialScene*>(args.id.getValue());
	if (scene == nullptr) {
		return false;
	}
	auto m = scene->getMaterial();
	m->ambient = args.ambient.getValue();
	m->diffuse = args.diffuse.getValue();
	m->specular = args.specular.getValue();
	m->shininess = args.shininess.getValue();
	scene->setName(args.name.getValue());
	return true;
}
