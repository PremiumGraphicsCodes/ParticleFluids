#include "PSBoxView.h"

#include "../../Crystal/Graphics/ColorRGBA.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSBoxView::PSBoxView(const std::string& name, World* world, Canvas* canvas) :
	IPSAddView("PSBox", world, canvas),
	boxView("Box"),
	countView("Count", 10000),
	isVolumeView("Volume", false)
{
	add(&boxView);
	add(&countView);
	add(&isVolumeView);
};

void PSBoxView::onOk()
{
	const auto& b = boxView.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	if (isVolumeView.getValue()) {
		for (int i = 0; i < countView.getValue(); ++i) {
			const auto u = dist(mt);
			const auto v = dist(mt);
			const auto w = dist(mt);
			positions.push_back(b.getPosition(u, v, w));
		}
	}
	else {
		for (int i = 0; i < countView.getValue(); ++i) {
			const auto u = dist(mt);
			const auto v = dist(mt);
			positions.push_back(b.getPosition(1.0, u, v));
		}
	}
	IPSAddView::addParticleSystem(positions);
}