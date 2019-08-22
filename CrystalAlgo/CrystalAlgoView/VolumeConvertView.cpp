#include "VolumeConvertView.h"

#include "../CrystalAlgo/VolumeConvertAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Algo;

VolumeConvertView::VolumeConvertView(World* model, Canvas* canvas) :
	IOkCancelView("VolumeConvert", model, canvas),
	objectButton("ParticleSystem", model, canvas, Scene::SceneType::ParticleSystemScene),
	searchRadius("SearchRadius", 1.0)
{
}

void VolumeConvertView::onShow()
{
	objectButton.show();
}

void VolumeConvertView::onOk()
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
	getWorld()->getObjectFactory()->createParticleSystemScene(positions, attr, "VolumeConvert");
	getWorld()->updateViewModel();
}
