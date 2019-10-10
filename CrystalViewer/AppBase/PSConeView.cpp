#include "PSConeView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSConeView::PSConeView(World* model, Canvas* canvas) :
	IPSAddView("PSCone", model, canvas),
	cone("Cone"),
	count("Count", 10000)
{
	add(&cone);
	add(&count);
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
	IPSAddView::addParticleSystem(positions);
}
