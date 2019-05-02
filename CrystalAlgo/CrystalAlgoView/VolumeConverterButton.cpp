#include "VolumeConverterButton.h"

#include "../CrystalAlgo/VolumeConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Model;
using namespace Crystal::UI;
using namespace Crystal::Algo;

VolumeConverterButton::VolumeConverterButton(Repository* model, Canvas* canvas) :
	IPopupButton("VolumeConverter", model, canvas),
	objectButton("ParticleSystem", model, canvas, Model::ObjectType::ParticleSystemObject),
	searchRadius("SearchRadius", 1.0)
{
}

void VolumeConverterButton::onShow()
{
	objectButton.show();
}

void VolumeConverterButton::onOk()
{
	Math::Box3d box;
	Volume3d volume(32, 32, 32, box);

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
}

void VolumeConverterButton::onCancel()
{
}

