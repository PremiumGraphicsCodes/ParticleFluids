#include "PSBoxButton.h"

#include "imgui.h"

#include "../Graphics/ColorRGBA.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void PSBoxButton::onShow()
{
	boxButton.show();
	ImGui::InputInt("Count", &count);
}

void PSBoxButton::onOk()
{
	const auto& box = boxButton.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3df> positions;
	for (int i = 0; i < count; ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		const auto w = dist(mt);
		positions.push_back(box.getPosition(Vector3dd( u, v, w )));
	}
	getModel()->getObjects()->getParticleSystems()->addObject(positions, ColorRGBAf(1, 1, 1, 1), 100.0f, "Box");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
