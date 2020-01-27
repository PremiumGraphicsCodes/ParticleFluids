#include "PSSphereView.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"

#include "../Command/Command.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::UI;

PSSphereView::PSSphereView(const std::string& name, World* world, Canvas* canvas) :
	IPSAddView(name, world, canvas),
	sphereView("Sphere"),
	countView("Count", 10000)
{
	add(&sphereView);
	add(&countView);
}

void PSSphereView::onOk()
{
	const auto& shape = sphereView.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < countView.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(shape.getPosition(u, v, 1.0));
	}
	IPSAddView::addParticleSystem(positions);
}
