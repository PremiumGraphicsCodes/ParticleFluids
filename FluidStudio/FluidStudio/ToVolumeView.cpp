#include "ToVolumeView.h"


#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/VDBSceneFileImportCommand.h"
#include "CrystalVDB/VDBCommand/VDBSceneFileWriteCommand.h"
#include "CrystalVDB/VDBCommand/VDBScenePSToVolumeCommand.h"

#include "CrystalScene/Command/ParticleSystemCreateCommand.h"
#include "CrystalScene/Command/PLYFileImportCommand.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::VDB;
using namespace Crystal::UI;

using namespace PG::FS;

ToVolumeView::ToVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleRadiusView("ParticleRadius", 1.0),
	gridCellWidthView("GridCellWith", 0.5),
	inputDirectoryView("InputDir", "./"),
	outputDirectoryView("OutputDir", "./")
{
	add(&particleRadiusView);
	add(&gridCellWidthView);
	add(&inputDirectoryView);
	add(&outputDirectoryView);

}

void ToVolumeView::onOk()
{
	const auto path = inputDirectoryView.getPath();
	const auto outdir = outputDirectoryView.getPath();
	for (const auto& file : std::filesystem::directory_iterator(path)) {
		std::cout << file << std::endl;
		World w;

		VDBSceneFileImportCommand::Args readArgs;
		readArgs.filePath.setValue(file.path().string());
		readArgs.fileFormat.setValue("PLY");
		VDBSceneFileImportCommand readCommand(readArgs);
		readCommand.execute(&w);
		//readCommand.getResult("NewId")

		VDBScenePSToVolumeCommand::Args cArgs;
		cArgs.radius.setValue(particleRadiusView.getValue());
		cArgs.voxelSize.setValue(gridCellWidthView.getValue());
		cArgs.sceneId.setValue(1);
		VDBScenePSToVolumeCommand cCommand(cArgs);
		cCommand.execute(&w);

		VDBSceneFileWriteCommand::Args wArgs;
		std::filesystem::path wFilePath(outdir);
		wFilePath.append(file.path().stem().string() + ".vdb");
		wArgs.vdbSceneId.setValue(2);
		wArgs.filePath.setValue(wFilePath.string());
		VDBSceneFileWriteCommand wCommand(wArgs);
		wCommand.execute(&w);
	}
}
