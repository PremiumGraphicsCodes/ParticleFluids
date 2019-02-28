#include "PSConeButton.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void PSConeButton::onShow()
{
	cone.show();
	attribute.show();
	count.show();
}

void PSConeButton::onOk()
{
	const auto& c = cone.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3df> positions;
	for (int i = 0; i < count.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(c.getPosition(u, v));
	}
	getModel()->getObjects()->getParticleSystems()->addObject(positions, attribute.getValue(), "Cylinder");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
