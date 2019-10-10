#include "PCDFileImportCommand.h"

#include "../../Crystal/IO/PCDFileReader.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string PCDFileImportCommand::getName()
{
	return "PCDFileImport";
}

void PCDFileImportCommand::execute(Crystal::Scene::World* scene)
{
	PCDFileReader reader;
	if (reader.read(args.filePath.getValue())) {
		const auto& positions = reader.getPCD().data.positions;
		ParticleAttribute attr;
		attr.color = glm::vec4(0, 0, 0, 0);
		attr.size = 1.0;
		scene->getObjects()->addScene(scene->getObjectFactory()->createParticleSystemScene(positions, attr, "PCD"));
	}
}