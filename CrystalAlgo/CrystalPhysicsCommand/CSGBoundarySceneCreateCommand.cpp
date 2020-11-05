#include "CSGBoundarySceneCreateCommand.h"

#include "PublicLabels/CSGBoundarySceneCreateLabels.h"

#include "../CrystalPhysics/CSGBoundaryScene.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/Command/Public/PublicLabel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string CSGBoundarySceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

CSGBoundarySceneCreateCommand::Args::Args() :
	box(::BoxLabel, Math::Box3d()),
	name(::NameLabel, std::string("CSGBoundary"))
{
	add(&box);
	add(&name);
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
	auto boundaryScene = new CSGBoundaryScene(world->getNextSceneId(), args.name.getValue());
	boundaryScene->add(args.box.getValue());

	results.newId.setValue(boundaryScene->getId());

	return true;
}