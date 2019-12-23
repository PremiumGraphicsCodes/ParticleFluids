#include "MaterialUpdateCommand.h"

#include "Public/MaterialUpdateLabels.h"
#include "../../Crystal/Scene/MaterialScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string MaterialUpdateCommand::getName()
{
	return MaterialUpdateLabels::CommandNameLabel;
}

MaterialUpdateCommand::Args::Args() :
	id(MaterialUpdateLabels::IdLabel, -1),
	ambient(MaterialUpdateLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(MaterialUpdateLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(MaterialUpdateLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	shininess(MaterialUpdateLabels::ShininessLabel, 1.0f),
	textureId(MaterialUpdateLabels::TextureIdLabel, -1),
	name(MaterialUpdateLabels::NameLabel, std::string(""))
{
	add(&id);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	add(&textureId);
	add(&name);
}

void MaterialUpdateCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<MaterialScene*>(args.id.getValue());
	auto m = scene->getMaterial();
	m.ambient = args.ambient.getValue();
	m.diffuse = args.diffuse.getValue();
	m.specular = args.specular.getValue();
	m.shininess = args.shininess.getValue();
	m.textureId = args.textureId.getValue();
	scene->setMaterial(m);
	scene->setName(args.name.getValue());
}
