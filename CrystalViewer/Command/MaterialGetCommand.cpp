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
//	textureName(MaterialGetLabels::TextureNameLabel, std::string("")),
	name(MaterialGetLabels::NameLabel, std::string(""))
{
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
//	add(&textureName);
	add(&name);
}

void MaterialGetCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<MaterialScene*>(args.id.getValue());
	if (scene == nullptr) {
		return;
	}
	auto m = scene->getMaterial();
	results.ambient.setValue(Graphics::ColorRGBAf(m.ambient));
	results.diffuse.setValue(Graphics::ColorRGBAf(m.diffuse));
	results.specular.setValue(Graphics::ColorRGBAf(m.specular));
	results.shininess.setValue(m.shininess);
//	results.textureName.setValue(m.ambientTextureName);
	results.name.setValue(scene->getName());
}
