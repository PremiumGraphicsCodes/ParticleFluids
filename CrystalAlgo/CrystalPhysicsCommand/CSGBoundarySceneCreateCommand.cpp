#include "CSGBoundarySceneCreateCommand.h"

#include "PublicLabels/CSGBoundarySceneCreateLabels.h"

#include "../CrystalPhysics/CSGBoundaryScene.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string CSGBoundarySceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

CSGBoundarySceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, 0)
{
	add(&newId);
}

CSGBoundarySceneCreateCommand::CSGBoundarySceneCreateCommand() :
	ICommand(&args, &results)
{}

bool CSGBoundarySceneCreateCommand::execute(World* world)
{
	auto boundaryScene = new CSGBoundaryScene(world->getNextSceneId(), "");
	world->getScenes()->addScene(boundaryScene);

	results.newId.setValue(boundaryScene->getId());

	return true;
}