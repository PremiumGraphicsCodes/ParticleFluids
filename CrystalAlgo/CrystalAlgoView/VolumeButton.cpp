#include "VolumeButton.h"

#include "../CrystalAlgo/Volume.h"
#include "../../Crystal/Math/Gaussian.h"

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
	Volume volume(32, 32, 32, box.getValue());

	auto function = [](double distance) {
		Gaussian gaussian;
		return gaussian.getValue(distance);
	};
	volume.add(function);


	const auto& particles = volume.toParticles();
	std::vector<Vector3df> positions;
	std::vector<double> values;
	for (const auto& p : particles) {
		positions.push_back(p.getPosition());
		values.push_back(p.getAttribute());
	}
	const auto minValue = std::min_element(values.begin(), values.end());
	const auto maxValue = std::max_element(values.begin(), values.end());
	ParticleAttribute attr;
	attr.color = glm::vec4(1, 0, 0, 0);
	attr.size = 1.0;
	getModel()->getObjects()->getParticleSystems()->addObject(positions, attr, "VolumeConverter");
	getCanvas()->setViewModel(getModel()->toViewModel());
}

void VolumeButton::onCancel()
{
}

