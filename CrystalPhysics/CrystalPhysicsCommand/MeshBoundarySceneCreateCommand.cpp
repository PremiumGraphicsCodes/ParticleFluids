#include "MeshBoundarySceneCreateCommand.h"

#include "PublicLabels/MeshBoundarySceneCreateLabels.h"

#include "../CrystalPhysics/MeshBoundaryScene.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string MeshBoundarySceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

MeshBoundarySceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, 0)
{
	add(&newId);
}

MeshBoundarySceneCreateCommand::MeshBoundarySceneCreateCommand() :
	ICommand(&args, &results)
{}

bool MeshBoundarySceneCreateCommand::execute(World* world)
{
	auto boundaryScene = new MeshBoundaryScene(world->getNextSceneId(), "");
	world->getScenes()->addScene(boundaryScene);

	results.newId.setValue(boundaryScene->getId());

	return true;
}