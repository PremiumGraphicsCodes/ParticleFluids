#include "FluidSimulationView.h"

#include "../CrystalPhysics/FluidScene.h"
#include "../CrystalPhysics/FluidSimulator.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../CrystalViewer/Command/Public/ShaderBuildLabels.h"
#include "../../CrystalViewer/Command/Public/CameraLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Algo::Physics;

FluidSimulationView::FluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("FluidSimulation", model, canvas)
{
}

void FluidSimulationView::onOk()
{
	auto world = getWorld();

	auto mp = new MacroParticle(1.0);
//	mp->distributePoints(10, 10);
	//FluidSimulator simulator;
	//simulator.addParticle(mp);
	//simulator.simulate(0.01);

	FluidScene* fps = new FluidScene(getWorld()->getNextSceneId(), "Fluid");
	fps->addParticle(mp);
	getWorld()->getObjects()->addScene(fps);
	auto newId = fps->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());


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

