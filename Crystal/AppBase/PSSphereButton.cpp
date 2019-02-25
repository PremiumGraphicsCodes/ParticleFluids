#include "PSSphereButton.h"

#include "imgui.h"

#include "../Math/Sphere3d.h"
#include "../Graphics/ColorRGBA.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void PSSphereButton::onShow()
{
	ImGui::InputFloat3("Center", &center[0]);
	ImGui::InputFloat("Radius", &radius);
	ImGui::InputFloat("Size", &size);
	ImGui::InputInt("Count", &count);
}

void PSSphereButton::onOk()
{
	const Crystal::Math::Sphere3d sphere(center, radius);
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3df> positions;
	for (int i = 0; i < count; ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(sphere.getPosition(u, v));
	}
	getModel()->getObjects()->getParticleSystems()->addObject(positions, ColorRGBAf(1, 1, 1, 1), size, "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
