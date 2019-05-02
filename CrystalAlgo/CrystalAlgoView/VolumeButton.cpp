#include "VolumeButton.h"

#include "../CrystalAlgo/Volume.h"

using namespace Crystal::Math;
using namespace Crystal::Model;
using namespace Crystal::UI;
using namespace Crystal::Algo;

VolumeButton::VolumeButton(Repository* model, Canvas* canvas) :
	IPopupButton("Volume", model, canvas),
	box("Box")
{
}

void VolumeButton::onShow()
{
	box.show();
}

void VolumeButton::onOk()
{
	/*
	Math::Box3d box;
	Volume volume(32, 32, 32, box);

	VolumeConverter converter;
	//converter.convert(volume, );

	const auto& particles = volume.toParticles();
	std::vector<Vector3df> positions;
	for (const auto& p : particles) {
		positions.push_back(p.getPosition());
	}
	ParticleAttribute attr;
	attr.color = glm::vec4(1, 0, 0, 0);
	attr.size = 1.0;
	getModel()->getObjects()->getParticleSystems()->addObject(positions, attr, "VolumeConverter");
	getCanvas()->setViewModel(getModel()->toViewModel());
	*/
}

void VolumeButton::onCancel()
{
}

