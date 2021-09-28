#include "PCDFileImportCommand.h"

#include "../../Crystal/IO/PCDFileReader.h"
#include "../Scene/ParticleSystemScene.h"

#include "Public/PCDFileImportLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PCDFileImportCommand::Args::Args() :
	filePath(PCDFileImportLabels::FilePathLabel, "")
{
	add(&filePath);
}

PCDFileImportCommand::Results::Results() :
	newId(PCDFileImportLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string PCDFileImportCommand::getName()
{
	return PCDFileImportLabels::CommandNameLabel;
}

bool PCDFileImportCommand::execute(Crystal::Scene::World* scene)
{
	PCDFileReader reader;
	if (reader.read(args.filePath.getValue())) {
		const auto& positions = reader.getPCD().data.positions;
		ParticleAttribute attr;
		attr.color = glm::vec4(0, 0, 0, 0);
		attr.size = 1.0;
		auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
		auto s = new ParticleSystemScene(scene->getNextSceneId(), "PCD", std::move(shape));
		scene->getScenes()->addScene(s);
		results.newId.setValue(s->getId());
		//results.isOk.setValue( true );
		return true;
	}
	return false;
}