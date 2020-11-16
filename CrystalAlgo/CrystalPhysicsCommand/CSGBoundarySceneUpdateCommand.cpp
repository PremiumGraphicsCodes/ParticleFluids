#include "CSGBoundarySceneUpdateCommand.h"

#include "PublicLabels/CSGBoundarySceneUpdateLabels.h"

#include "../CrystalPhysics/CSGBoundaryScene.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/Command/Public/PublicLabel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string CSGBoundarySceneUpdateCommand::getName()
{
	return ::CommandNameLabel;
}

CSGBoundarySceneUpdateCommand::Args::Args() :
	id(::IdLabel, -1),
	box(::BoxLabel, Math::Box3d()),
	name(::NameLabel, std::string("CSGBoundary"))
{
	add(&id);
	add(&box);
	add(&name);
}

CSGBoundarySceneUpdateCommand::Results::Results()
{
}

CSGBoundarySceneUpdateCommand::CSGBoundarySceneUpdateCommand() :
	ICommand(&args, &results)
{}

bool CSGBoundarySceneUpdateCommand::execute(World* world)
{
	auto boundaryScene = world->getScenes()->findSceneById<CSGBoundaryScene*>(args.id.getValue());
	boundaryScene->clear();
	boundaryScene->setName(args.name.getValue());
	boundaryScene->add(args.box.getValue());
	world->getScenes()->addScene(boundaryScene);

	//results.newId.setValue(boundaryScene->getId());

	return true;
}