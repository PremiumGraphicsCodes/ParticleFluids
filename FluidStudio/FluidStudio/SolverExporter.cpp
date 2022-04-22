#include "SolverExporter.h"

#include "CrystalScene/Scene/IAnimator.h"
#include "CrystalPhysics/CrystalPhysicsCommand/PhysicsSolverExportCommand.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;

SolverExporter::SolverExporter(World* model) :
	world(model),
	solver(nullptr),
	frame(0)
{}

void SolverExporter::step()
{
	if (!isActive) {
		return;
	}

	if (solver == nullptr) {
		return;
	}


	const auto timeStep = solver->getTimeStep();

	if (timeStep % interval != 0) {
		return;
	}

	auto fileName = path;
	fileName.append("particle" + std::to_string(frame) + ".ply");

	const auto fluids = solver->getFluids();
	const auto emitters = solver->getEmitters();
	//solver->
	PhysicsSolverExportCommand::Args args;
	std::vector<int> ids;
	for (auto f : fluids) {
		ids.push_back(f->getId());
	}
	for (auto e : emitters) {
		ids.push_back(e->getId());
	}
	args.fluidIds.setValue(ids);
	args.doExportMicro.setValue(true);
	args.filePath.setValue(fileName.string());
	PhysicsSolverExportCommand command(args);
	command.execute(world);

	frame++;
}