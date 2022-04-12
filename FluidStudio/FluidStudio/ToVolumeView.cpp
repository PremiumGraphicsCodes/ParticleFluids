#include "ToVolumeView.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "CrystalPhysics/CrystalPhysicsCommand/SPHVolumeConvertCommand.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;

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
