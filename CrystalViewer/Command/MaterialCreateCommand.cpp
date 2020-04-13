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
	ambientTextureName(MaterialCreateLabels::AmbientTextureNameLabel, std::string("")),
	diffuseTextureName(MaterialCreateLabels::DiffuseTextureNameLabel, std::string("")),
	specularTextureName(MaterialCreateLabels::SpecularTextureNameLabel, std::string("")),
	name(MaterialCreateLabels::NameLabel, std::string(""))
{
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	add(&ambientTextureName);
	add(&diffuseTextureName);
	add(&specularTextureName);
	add(&name);
}

MaterialCreateCommand::Results::Results() :
	newId(MaterialCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

bool MaterialCreateCommand::execute(World* world)
{
	auto m = std::make_unique<Material>();

	m->ambient = args.ambient.getValue();
	m->diffuse = args.diffuse.getValue();
	m->specular = args.specular.getValue();
	m->shininess = args.shininess.getValue();

	//m.ambientTextureName = args.ambientTextureName.getValue();
	//m.diffuseTextureName = args.diffuseTextureName.getValue();
	//m.specularTextureName = args.specularTextureName.getValue();

	auto scene = new MaterialScene(world->getSceneFactory()->getNextId(), "BlackMat", std::move(m) );
	world->getObjects()->addScene(scene);
	results.newId.setValue(scene->getId());

	return true;
}
