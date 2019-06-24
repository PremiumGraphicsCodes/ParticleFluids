#include "PSCylinderButton.h"

#include "imgui.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void PSCylinderButton::onShow()
{
	cylinderButton.show();
	attribute.show();
	ImGui::InputInt("Count", &count);
}

void PSCylinderButton::onOk()
{
	const auto& cylinder = cylinderButton.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < count; ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(cylinder.getPosition(1.0, u, v));
	}
	getModel()->getObjects()->getParticleSystems()->addObject(positions, attribute.getValue(), "Cylinder");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

