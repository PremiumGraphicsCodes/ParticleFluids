#include "SpaceHashView.h"

#include "../CrystalAlgo/SpaceHash3d.h"
#include "../../Crystal/Shape/ParticleSystem.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Search;

SpaceHashView::SpaceHashView(World* model, Canvas* canvas) :
	IOkCancelView("SpaceHash", model, canvas),
	searchRadius("SearchRadius", 1.0)
{
	add(&searchRadius);
}

void SpaceHashView::onOk()
{
	ParticleSystem<void*> ps;
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			for (int k = 0; k < 100; ++k) {
				ps.add(Vector3dd(i, j, k), nullptr);
			}
		}
	}

	SpaceHash3d grid(searchRadius.getValue(), 10000000);
	const auto particles = ps.getIParticles();
	for (auto p : particles) {
		grid.add(p);
	}
	auto func = [](IPoint* lhs, IPoint* rhs) {
		return;
	};
	for (auto p : particles) {
		grid.solveInteractions(p, func);
	}
	std::cout << "Search Completed" << std::endl;
}