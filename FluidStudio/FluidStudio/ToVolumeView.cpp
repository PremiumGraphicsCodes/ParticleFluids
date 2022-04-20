#include "ToVolumeView.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "CrystalPhysics/CrystalPhysics/FluidVolumeScene.h"
#include "CrystalPhysics/CrystalPhysics/SurfaceConstruction/SPHVolumeConverter.h"
#include "CrystalPhysics/CrystalPhysics/FluidVolumeScene.h"
#include "CrystalPhysics/CrystalPhysicsCommand/SPHVolumeConvertCommand.h"
#include "CrystalPhysics/CrystalPhysicsCommand/FluidVolumeExportCommand.h"

#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/VDBPLYFileReadCommand.h"
#include "CrystalVDB/VDBCommand/VDBSceneCreateCommand.h"
#include "CrystalVDB/VDBCommand/VDBPLYFileReadCommand.h"
#include "CrystalVDB/VDBCommand/VDBFileWriteCommand.h"
#include "CrystalVDB/VDBCommand/VDBPSToVolumeCommand.h"

#include "CrystalScene/Command/ParticleSystemCreateCommand.h"
#include "CrystalScene/Command/PLYFileImportCommand.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;
using namespace Crystal::Command;
using namespace Crystal::VDB;

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

		VDBSceneCreateCommand::Args scArgs;
		scArgs.sceneType.setValue("VDBPoints");
		VDBSceneCreateCommand scCommand(scArgs);
		scCommand.execute(&w);
		const auto vdbPointsId = std::any_cast<int>(scCommand.getResult("NewId"));

		VDBPLYFileReadCommand::Args readArgs;
		readArgs.vdbSceneId.setValue(vdbPointsId);
		readArgs.isVolume.setValue(false);
		readArgs.filePath.setValue(file.path().string());
		VDBPLYFileReadCommand readCommand(readArgs);
		readCommand.execute(&w);

		VDBSceneCreateCommand::Args scArgs2;
		scArgs2.sceneType.setValue("VDBVolume");
		scArgs2.name.setValue("density");
		VDBSceneCreateCommand scCommand2(scArgs2);
		scCommand2.execute(&w);
		const auto vdbVolumeId = std::any_cast<int>(scCommand2.getResult("NewId"));

		VDBPSToVolumeCommand::Args cArgs;
		cArgs.doUseSph.setValue(true);
		cArgs.radius.setValue(1.0);
		cArgs.voxelSize.setValue(0.5);
		cArgs.particleSystemId.setValue(vdbPointsId);
		cArgs.vdbVolumeId.setValue(vdbVolumeId);
		VDBPSToVolumeCommand cCommand(cArgs);
		cCommand.execute(&w);

		VDBFileWriteCommand::Args wArgs;
		std::filesystem::path wFilePath(outdir);
		wFilePath.append(file.path().stem().string() + ".vdb");
		wArgs.vdbVolumeIds.setValue(std::vector<int>{ vdbVolumeId });
		wArgs.filePath.setValue(wFilePath.string());
		VDBFileWriteCommand wCommand(wArgs);
		wCommand.execute(&w);

		/*
		ParticleSystemCreateCommand psCreateCommand;
		psCreateCommand.execute(&w);
		const auto psId = std::any_cast<int>(psCreateCommand.getResult("NewId"));

		auto fluidVolumeScene = new FluidVolumeScene(w.getNextSceneId(), "", std::make_unique<SparseVolumef>());
		w.addScene(fluidVolumeScene);
		const auto volumeId = fluidVolumeScene->getId();


		std::cout << file.path() << std::endl;
		PLYFileImportCommand::Args iArgs;
		iArgs.filePath.setValue(file.path().string());
		iArgs.particleSystemId.setValue(psId);
		PLYFileImportCommand importCommand(iArgs);
		importCommand.execute(&w);

		SPHVolumeConvertCommand::Args args;
		args.isIsotorpic.setValue(true);
		args.particleRadius.setValue(particleRadiusView.getValue());
		args.cellLength.setValue(gridCellWidthView.getValue());
		args.volumeId.setValue(volumeId);
		args.particleSystemId.setValue(psId);
		SPHVolumeConvertCommand command(args);
		command.execute(&w);

		FluidVolumeExportCommand::Args eArgs;
		std::filesystem::path eFilePath(outdir);
		eFilePath.append(file.path().filename().string());
		std::cout << eFilePath << std::endl;
		eArgs.filePath.setValue(eFilePath.string());
		eArgs.volumeId.setValue(volumeId);
		FluidVolumeExportCommand exportCommand(eArgs);
		exportCommand.execute(&w);

		VDBSceneCreateCommand::Args scArgs;
		scArgs.sceneType.setValue("VDBVolume");
		VDBSceneCreateCommand scCommand(scArgs);
		scCommand.execute(&w);
		const auto vdbVolumeId = std::any_cast<int>(scCommand.getResult("NewId"));

		VDBPLYFileReadCommand::Args vArgs;
		vArgs.filePath.setValue(eFilePath.string());
		vArgs.isVolume.setValue(true);
		vArgs.vdbSceneId.setValue(vdbVolumeId);
		VDBPLYFileReadCommand vdbReadCommand(vArgs);
		vdbReadCommand.execute(&w);

		VDBFileWriteCommand::Args wArgs;
		std::filesystem::path wFilePath(outdir);
		wFilePath.append(file.path().stem().string() + ".vdb");
		wArgs.vdbVolumeIds.setValue(std::vector<int>{ vdbVolumeId });
		wArgs.filePath.setValue(wFilePath.string());
		VDBFileWriteCommand wCommand(wArgs);
		wCommand.execute(&w);
		*/
	}

	/*
	ToVDBVolumeCommand command;
	command.execute(getWorld());
	auto volume = new VDBVolumeScene(getWorld()->getNextSceneId(), "VDBVolume");
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto dist = i * i + j * j + k * k;
				const auto v = std::sqrt(dist) / 10.0;
				volume->setValue({ i,j,k }, v);
			}
		}
	}
	volume->setScale(scaleView.getValue());

	volume->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(volume);
	*/
}
