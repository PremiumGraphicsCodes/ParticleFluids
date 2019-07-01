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
	std::vector<Vector3dd> positions;
	for (int i = 0; i < count.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(c.getPosition(Vector3dd(u, v, 1.0)));
	}
	auto scene = getModel()->getObjects()->getFactory()->createParticleSystemScene(positions, attribute.getValue(), "Cylinder");
	getModel()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
