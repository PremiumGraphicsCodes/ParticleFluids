#include "TextureCreateCommand.h"

#include "Public/TextureCreateLabels.h"

#include "../../Crystal/Scene/TextureScene.h"
#include "../../Crystal/IO/ImageFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::IO;
using namespace Crystal::Command;

std::string TextureCreateCommand::getName()
{
	return TextureCreateLabels::CommandNameLabel; //MaterialCreateLabels::CommandNameLabel;
}

TextureCreateCommand::Args::Args() :
	filePath(TextureCreateLabels::FilePathLabel, std::string("")),
	name(TextureCreateLabels::NameLabel, std::string(""))
{
	add(&filePath);
	add(&name);
}

TextureCreateCommand::Results::Results() :
	newId(TextureCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

bool TextureCreateCommand::execute(World* world)
{
	ImageFileReader reader;
	const auto isOk = reader.read(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	auto image = std::make_unique<Image>();
	*image = reader.getImage();
	auto scene = world->getSceneFactory()->createTextureScene(std::move(image), args.name.getValue());
//	scene->build(*world->getGLFactory());
//	scene->send();
	world->getObjects()->addScene(scene);
	world->getRenderer()->getObjectRenderer()->add(scene);
	results.newId.setValue(scene->getId());
	return true;
}
