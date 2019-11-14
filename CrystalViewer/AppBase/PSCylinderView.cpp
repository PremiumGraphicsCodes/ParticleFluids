#include "PSCylinderView.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSCylinderView::PSCylinderView(World* model, Canvas* canvas) :
	IPSAddView("PSCylinder", model, canvas),
	cylinder("Cylinder"),
	count("Count", 10000)
{
	add(&cylinder);
	add(&count);
}

void PSCylinderView::onOk()
{
	const auto& cylinder = this->cylinder.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < count.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(cylinder.getPosition(u, v, 1.0));
	}
	IPSAddView::addParticleSystem(positions);
}

