#include "PCDFileImportCommand.h"

#include "../../Crystal/IO/PCDFileReader.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "Public/FileImportLabels.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PCDFileImportCommand::Args::Args() :
	filePath(FileImportLabels::FilePathLabel, "")
{
	add(&filePath);
}

PCDFileImportCommand::Results::Results() :
	isOk(FileImportLabels::IsOkLabel, false)
{
	add(&isOk);
}

std::string PCDFileImportCommand::getName()
{
	return FileImportLabels::PCDFileImportCommandLabel;
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
		results.isOk.setValue( true );
	}
}