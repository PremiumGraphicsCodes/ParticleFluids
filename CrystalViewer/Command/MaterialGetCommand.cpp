#include "MaterialGetCommand.h"

#include "Public/MaterialGetLabels.h"
#include "../../Crystal/Scene/MaterialScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string MaterialGetCommand::getName()
{
	return MaterialGetLabels::CommandNameLabel;
}

MaterialGetCommand::Args::Args() :
	id(MaterialGetLabels::IdLabel, -1)
{
	add(&id);
}

MaterialGetCommand::Results::Results() :
	ambient(MaterialGetLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(MaterialGetLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(MaterialGetLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	shininess(MaterialGetLabels::ShininessLabel, 1.0f),
	textureId(MaterialGetLabels::TextureIdLabel, -1),
	name(MaterialGetLabels::NameLabel, std::string(""))
{
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	add(&textureId);
	add(&name);
}

void MaterialGetCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<MaterialScene*>(args.id.getValue());
	if (scene == nullptr) {
		return;
	}
	auto m = scene->getMaterial();
	results.ambient.setValue(m.ambient);
	results.diffuse.setValue(m.diffuse);
	results.specular.setValue(m.specular);
	results.shininess.setValue(m.shininess);
	results.textureId.setValue(m.textureId);
	results.name.setValue(scene->getName());
}
