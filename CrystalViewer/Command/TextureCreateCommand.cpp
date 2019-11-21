#include "TextureCreateCommand.h"

#include "../../Crystal/IO/ImageFileReader.h"

//#include "Public/MaterialCreateLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::IO;
using namespace Crystal::Command;

std::string TextureCreateCommand::getName()
{
	return "TextureCreate"; //MaterialCreateLabels::CommandNameLabel;
}

TextureCreateCommand::Args::Args() :
	filePath("FilePath", std::string("")),
	name("Name", std::string(""))
{
	add(&filePath);
}

TextureCreateCommand::Results::Results() :
	newId("NewId", -1) //MaterialCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

void TextureCreateCommand::execute(World* world)
{
	ImageFileReader reader;
	const auto isOk = reader.read(args.filePath.getValue());
	if (!isOk) {
		return;
	}
	auto scene = world->getObjectFactory()->create(m, args.name.getValue());
	world->getObjects()->addScene(scene);
	results.newId.setValue(scene->getId());
}
