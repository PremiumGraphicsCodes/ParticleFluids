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
	sphere.show();
	size.show();
	count.show();
}

void PSSphereButton::onOk()
{
	const auto& shape = sphere.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3df> positions;
	for (int i = 0; i < count.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(shape.getPosition(u, v));
	}
	getModel()->getObjects()->getParticleSystems()->addObject(positions, ColorRGBAf(1, 1, 1, 1), size.getValue(), "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
