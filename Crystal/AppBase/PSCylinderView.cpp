#include "PSCylinderView.h"

#include "imgui.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

PSCylinderView::PSCylinderView(Repository* model, Canvas* canvas) :
	IPanel("PSCylinder", model, canvas),
	attribute("Attribute"),
	cylinderButton("Cylinder"),
	count("Count", 10000),
	ok("OK")
{
	ok.setFunction([=]() {onOk(); });
}

void PSCylinderView::show()
{
	cylinderButton.show();
	attribute.show();
	count.show();
	ok.show();
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
	auto scene = getRepository()->getObjectFactory()->createParticleSystemScene(positions, attribute.getValue(), "Cylinder");
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}

