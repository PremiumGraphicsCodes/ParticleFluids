#include "PSBoxButton.h"

#include "imgui.h"

#include "../Graphics/ColorRGBA.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void PSBoxButton::onShow()
{
	box.show();
	attribute.show();
	count.show();
	isVolume.show();
}

void PSBoxButton::onOk()
{
	const auto& b = box.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	if (isVolume.getValue()) {
		for (int i = 0; i < count.getValue(); ++i) {
			const auto u = dist(mt);
			const auto v = dist(mt);
			const auto w = dist(mt);
			positions.push_back(b.getPosition(Vector3dd(u, v, w)));
		}
	}
	else {
		for (int i = 0; i < count.getValue(); ++i) {
			const auto u = dist(mt);
			const auto v = dist(mt);
			positions.push_back(b.getPosition(Vector3dd(1.0, u, v)));
		}
	}

	getModel()->getObjects()->getFactory()->addParticleSystemScene(positions, attribute.getValue(), "Box");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
