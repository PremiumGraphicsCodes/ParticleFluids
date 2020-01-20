#include "MaterialCreateCommand.h"

#include "Public/MaterialCreateLabels.h"
#include "../../Crystal/Scene/MaterialScene.h"

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
//	textureName(MaterialCreateLabels::TextureNameLabel, ""),
	name(MaterialCreateLabels::NameLabel, std::string(""))
{
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	//add(&textureName);
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
	//m.ambientTextureName = args.textureName.getValue();
	auto scene = world->getSceneFactory()->createMaterialScene(m, args.name.getValue());
	world->getObjects()->addScene(scene);
	results.newId.setValue(scene->getId());
}
