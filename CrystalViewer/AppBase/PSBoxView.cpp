#include "PSBoxView.h"

#include "../../Crystal/Graphics/ColorRGBA.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSBoxView::PSBoxView(World* model, Canvas* canvas) :
	IPSAddView("PSBox", model, canvas),
	box("Box"),
	count("Count", 10000),
	isVolume("Volume", false)
{
	add(&box);
	add(&count);
	add(&isVolume);
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
	IPSAddView::addParticleSystem(positions);
}