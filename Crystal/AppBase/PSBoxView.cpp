#include "PSBoxView.h"

#include "../Graphics/ColorRGBA.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSBoxView::PSBoxView(World* model, Canvas* canvas) :
	IOkCancelView("PSBox", model, canvas),
	box("Box"),
	attribute("Attribute"),
	count("Count", 10000),
	isVolume("Volume", false),
	name("Name", "PSBox")
{
	add(&box);
	add(&attribute);
	add(&count);
	add(&isVolume);
	add(&name);
};

void PSBoxView::onOk()
{
	const auto& b = box.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	if (isVolume.getValue()) {
		for (int i = 0; i < count.getValue(); ++i) {
			const auto u = dist(mt);
			const auto v = dist(mt);
			const auto w = dist(mt);
			positions.push_back(b.getPosition(Vector3dd(u, v, w)));
		}
	}
	else {
		for (int i = 0; i < count.getValue(); ++i) {
			const auto u = dist(mt);
			const auto v = dist(mt);
			positions.push_back(b.getPosition(Vector3dd(1.0, u, v)));
		}
	}

	auto repository = getWorld();
	auto scene = repository->getObjectFactory()->createParticleSystemScene(positions, attribute.getValue(), name.getValue());
	repository->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(repository->getBoundingBox());
}