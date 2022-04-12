#include "ToVDBVolumeView.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "CrystalVDB/VDBCommand/ToVDBVolumeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

ToVDBVolumeView::ToVDBVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	scaleView("Scale", 1.0)
{
	add(&scaleView);
}

void ToVDBVolumeView::onOk()
{
	ToVDBVolumeCommand command;
	command.execute(getWorld());
	/*
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
