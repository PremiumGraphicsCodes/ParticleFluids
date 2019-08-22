#include "PSTorusView.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSTorusView::PSTorusView(World* model, Canvas* canvas) :
	IOkCancelView("PSTorus", model, canvas),
	torusView("Torus"),
	attribute("Attribute"),
	count("Count", 10000)
{
}

void PSTorusView::onShow()
{
	torusView.show();
	attribute.show();
	count.show();
}

void PSTorusView::onOk()
{
	const auto& shape = torusView.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < count.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(shape.getPosition(u, v));
	}
	auto scene = getWorld()->getObjectFactory()->createParticleSystemScene(positions, attribute.getValue(), "Cylinder");
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
