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
	attribute.show();
	count.show();
}

void PSSphereButton::onOk()
{
	const auto& shape = sphere.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < count.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(shape.getPosition(Vector3dd(u, v, 1.0)));
	}
	getModel()->getObjects()->getParticleSystems()->addObject(positions, attribute.getValue(), "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
