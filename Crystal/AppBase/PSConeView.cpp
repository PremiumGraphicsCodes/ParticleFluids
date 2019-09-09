#include "PSConeView.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSConeView::PSConeView(World* model, Canvas* canvas) :
	IOkCancelView("PSCone", model, canvas),
	cone("Cone"),
	attribute("Attribute"),
	count("Count", 10000),
	name("Name", "PSCone")
{
	add(&cone);
	add(&attribute);
	add(&count);
	add(&name);
}

void PSConeView::onOk()
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
	auto scene = getWorld()->getObjectFactory()->createParticleSystemScene(positions, attribute.getValue(), name.getValue());
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
