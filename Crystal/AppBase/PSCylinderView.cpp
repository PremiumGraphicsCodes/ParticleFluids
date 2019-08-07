#include "PSCylinderView.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSCylinderView::PSCylinderView(World* model, Canvas* canvas) :
	IOkCancelView("PSCylinder", model, canvas),
	attribute("Attribute"),
	cylinderButton("Cylinder"),
	count("Count", 10000)
{
}

void PSCylinderView::show()
{
	cylinderButton.show();
	attribute.show();
	count.show();
	IOkCancelView::show();
}

void PSCylinderView::onOk()
{
	const auto& cylinder = cylinderButton.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < count.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(cylinder.getPosition(Vector3dd( u, v, 1.0)));
	}
	auto scene = getWorld()->getObjectFactory()->createParticleSystemScene(positions, attribute.getValue(), "Cylinder");
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}

