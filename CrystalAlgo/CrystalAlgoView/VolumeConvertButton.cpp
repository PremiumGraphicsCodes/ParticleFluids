#include "VolumeConvertButton.h"

#include "../CrystalAlgo/VolumeConvertAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Algo;

VolumeConvertButton::VolumeConvertButton(RootScene* model, Canvas* canvas) :
	IPopupButton("VolumeConvert", model, canvas),
	objectButton("ParticleSystem", model, canvas, Scene::SceneType::ParticleSystemScene),
	searchRadius("SearchRadius", 1.0)
{
}

void VolumeConvertButton::onShow()
{
	objectButton.show();
}

void VolumeConvertButton::onOk()
{
	Math::Box3d box;
	Volume volume(32, 32, 32, box);

	VolumeConvertAlgo converter;
	//converter.convert(volume, );

	const auto& particles = volume.toParticles();
	std::vector<Vector3dd> positions;
	for (const auto& p : particles) {
		positions.push_back(p.getPosition());
	}
	ParticleAttribute attr;
	attr.color = glm::vec4(1, 0, 0, 0);
	attr.size = 1.0;
	getModel()->getObjectFactory()->createParticleSystemScene(positions, attr, "VolumeConvert");
	getCanvas()->setViewModel(getModel()->toViewModel());
}

void VolumeConvertButton::onCancel()
{
}

