#include "PSSphereView.h"

#include "../Math/Sphere3d.h"
#include "../Graphics/ColorRGBA.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSSphereView::PSSphereView(RootScene* model, Canvas* canvas) :
	IPanel("PSSphere", model, canvas),
	sphere("Sphere"),
	attribute("Attribute"),
	count("Count", 10000),
	ok("OK")
{
	ok.setFunction([=]() {onOk(); });
}

void PSSphereView::show()
{
	sphere.show();
	attribute.show();
	count.show();
	ok.show();
}

void PSSphereView::onOk()
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
	auto scene = getRepository()->getObjectFactory()->createParticleSystemScene(positions, attribute.getValue(), "Sphere");
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
