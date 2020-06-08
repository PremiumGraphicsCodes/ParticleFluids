#include "FluidSimulationView.h"

#include "../CrystalPhysics/FluidParticleSystem.h"
#include "../CrystalPhysics/FluidSimulator.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Algo::Physics;

FluidSimulationView::FluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("FluidSimulation", model, canvas)
{
}

void FluidSimulationView::onOk()
{
	auto repository = getWorld();

	FluidSimulator simulator;
	//simulator.addParticle()
	simulator.simulate(0.01);

	//FluidParticleSystem fps(getWorld()->getNextSceneId(), "Fluid");

	/*
	getWorld()->addScene(1, )

	auto obj1 = repository->getObjects()->findSceneById<PolygonMeshScene*>(mesh1.getId());
	auto obj2 = repository->getObjects()->findSceneById<PolygonMeshScene*>(mesh2.getId());
	if (obj1 == nullptr || obj2 == nullptr) {
		return;
	}

	IntersectionAlgo algo;
	const auto isFound = algo.calculateIntersection(*obj1->getShape(), *obj2->getShape(), tolerance.getValue());
	if (isFound) {
		const auto& intersections = algo.getIntersections();
		std::vector<Math::Vector3dd> positions;
		for (const auto& i : intersections) {
			const auto& p = i.position;
			positions.push_back(p);
		}
		ParticleAttribute attr;
		attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
		attr.size = 1.0f;
		//repository->getSceneFactory()->createParticleSystemScene(positions, attr, "intersections");
		//getWorld()->updateViewModel();
	}
	*/
}

