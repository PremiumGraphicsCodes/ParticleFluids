#include "ToVolumeView.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "CrystalPhysics/CrystalPhysics/FluidVolumeScene.h"
#include "CrystalPhysics/CrystalPhysics/SurfaceConstruction/SPHVolumeConverter.h"
#include "CrystalPhysics/CrystalPhysics/FluidVolumeScene.h"
#include "CrystalPhysics/CrystalPhysicsCommand/SPHVolumeConvertCommand.h"
#include "CrystalPhysics/CrystalPhysicsCommand/FluidVolumeExportCommand.h"

#include "CrystalScene/Command/ParticleSystemCreateCommand.h"
#include "CrystalScene/Command/PLYFileImportCommand.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;
using namespace Crystal::Command;

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
	World w;

	ParticleSystemCreateCommand psCreateCommand;
	psCreateCommand.execute(&w);
	const auto psId = std::any_cast<int>( psCreateCommand.getResult("NewId") );

	auto fluidVolumeScene = new FluidVolumeScene(w.getNextSceneId(), "", std::make_unique<SparseVolumef>());
	w.addScene(fluidVolumeScene);
	const auto fluidVolumeId = fluidVolumeScene->getId();

	const auto path = inputDirectoryView.getPath();
	for (const auto& file : std::filesystem::directory_iterator(path)) {
		std::cout << file.path() << std::endl;
		PLYFileImportCommand importCommand;
		PLYFileImportCommand::Args iArgs;
		iArgs.filePath.setValue(file.path().string());
		iArgs.particleSystemId.setValue(psId);

			/*
		SPHVolumeConvertCommand::Args args;
		args.isIsotorpic.setValue(true);
		args.particleRadius.setValue(particleRadiusView.getValue());
		args.cellLength.setValue(gridCellWidthView.getValue());
		args.volumeId.setValue(fluidVolumeId);
		SPHVolumeConvertCommand command(args);
		command.execute(getWorld());
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
