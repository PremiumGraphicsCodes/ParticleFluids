#include "MaterialCreateCommand.h"

#include "Public/MaterialCreateLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string MaterialCreateCommand::getName()
{
	return MaterialCreateLabels::CommandNameLabel;
}

MaterialCreateCommand::Args::Args() :
	ambient(MaterialCreateLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(MaterialCreateLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(MaterialCreateLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	shininess(MaterialCreateLabels::ShininessLabel, 1.0f),
	textureId(MaterialCreateLabels::TextureIdLabel, -1),
	name(MaterialCreateLabels::NameLabel, std::string(""))
{
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	add(&textureId);
	add(&name);
}

MaterialCreateCommand::Results::Results() :
	newId(MaterialCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

void MaterialCreateCommand::execute(World* world)
{
	Material m;
	m.ambient = args.ambient.getValue();
	m.diffuse = args.diffuse.getValue();
	m.specular = args.specular.getValue();
	m.shininess = args.shininess.getValue();
	m.textureId = args.textureId.getValue();
	auto scene = world->getObjectFactory()->createMaterialScene(m, args.name.getValue());
	world->getObjects()->addScene(scene);
	results.newId.setValue(scene->getId());
}
