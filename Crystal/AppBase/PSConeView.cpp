#include "PSConeView.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

PSConeView::PSConeView(Repository* model, Canvas* canvas) :
	IPanel("PSCone", model, canvas),
	cone("Cone"),
	attribute("Attribute"),
	count("Count", 10000),
	okButton("OK")
{
}

void PSConeView::show()
{
	cone.show();
	attribute.show();
	count.show();
	okButton.show();
	okButton.setFunction([=]() { onOk(); });
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
	auto scene = getRepository()->getObjectFactory()->createParticleSystemScene(positions, attribute.getValue(), "Cylinder");
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
