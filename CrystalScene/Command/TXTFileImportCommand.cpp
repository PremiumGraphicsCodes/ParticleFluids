#include "TXTFileImportCommand.h"

#include "../../Crystal/IO/TXTFileReader.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace TXTFileImportLabels
{
	PublicLabel CommandNameLabel = "TXTFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TXTFileImportCommand::Args::Args() :
	filePath(TXTFileImportLabels::FilePathLabel, "")
{
	add(&filePath);
}

TXTFileImportCommand::Results::Results() :
	newId(TXTFileImportLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string TXTFileImportCommand::getName()
{
	return TXTFileImportLabels::CommandNameLabel;
}

bool TXTFileImportCommand::execute(Crystal::Scene::World* scene)
{
	TXTFileReader reader;
	const auto isOk = reader.read(args.filePath.getValue());

	if (!isOk) {
		return false;
	}
	const auto& positions = reader.getPositions();
	ParticleAttribute attr;
	attr.color = glm::vec4(0, 0, 0, 0);
	attr.size = 1.0;
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	auto s = new ParticleSystemScene(scene->getNextSceneId(), "TXT", std::move(shape));
	scene->getScenes()->addScene(s);
	results.newId.setValue(s->getId());
	return true;
}