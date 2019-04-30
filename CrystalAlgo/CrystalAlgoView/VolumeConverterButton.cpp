#include "VolumeConverterButton.h"

#include "../CrystalAlgo/VolumeConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Model;
using namespace Crystal::UI;
using namespace Crystal::Algo;

VolumeConverterButton::VolumeConverterButton(Repository* model, Canvas* canvas) :
	IPopupButton("VolumeConverter", model, canvas)//,
//	objectButton1("ParticleSystem", model, canvas, Model::ObjectType::ParticleSystemObject)
{
}

void VolumeConverterButton::onShow()
{
//	objectButton1.show();
}

void VolumeConverterButton::onOk()
{
	Math::Box3d box;
	Volume3d volume(32, 32, 32, box);

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

