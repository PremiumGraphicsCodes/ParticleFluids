#include "PCDFileExportCommand.h"

#include "../../Crystal/IO/PCDFileWriter.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "Public/FileExportLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::IO;

PCDFileExportCommand::Args::Args() :
	ids(FileExportLabels::IdsLabel, {}),
	filePath(FileExportLabels::FilePathLabel, "")
{
	add(&ids);
	add(&filePath);
}

PCDFileExportCommand::Results::Results()
{
//	add(&isOk);
}

std::string PCDFileExportCommand::getName()
{
	return FileExportLabels::PCDFileExportCommandLabel;
}

bool PCDFileExportCommand::execute(World* world)
{
	const auto& ids = args.ids.getValue();
	auto scenes = world->getObjects()->findScenes(SceneType::ParticleSystemScene);

	PCDFile file;
	for (const auto& id : ids) {
		auto scene = world->getObjects()->findSceneById<ParticleSystemScene*>(id);
		const auto& ps = scene->getShape()->getParticles();
		for (auto p : ps) {
			file.data.positions.push_back(p->getPosition());
		}
	}
	file.header.width = file.data.positions.size();
	file.header.points = file.data.positions.size();
	PCDFileWriter writer;
	std::filesystem::path filePath(args.filePath.getValue());
	const auto isOk = writer.write(filePath, file);
	//this->results.isOk.setValue( isOk );
	return isOk;
}
