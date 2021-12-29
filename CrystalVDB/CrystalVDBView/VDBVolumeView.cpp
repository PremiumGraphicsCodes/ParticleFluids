#include "VDBVolumeView.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBVolumeView::VDBVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	scaleView("Scale", 1.0)
{
	add(&scaleView);
}

void VDBVolumeView::onOk()
{
	auto volume = new VDBVolumeScene(getWorld()->getNextSceneId(), "VDBVolume");
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				volume->setValue({ i,j,k }, 10);
			}
		}
	}
	volume->setScale(scaleView.getValue());

	volume->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(volume);
}
