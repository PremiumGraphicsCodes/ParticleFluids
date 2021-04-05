#include "SparseVolumeSceneCreateCommand.h"

//#include "../../Crystal/Scene/ParticleAttribute.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "PublicLabels/SparseVolumeSceneCreateLabels.h"

using namespace Crystal::Math;
//using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SparseVolumeSceneCreateCommand::Args::Args() :
	resolutions(::ResolutionLabel, {10, 10, 10}),
	boundingBox(::BoundingBoxLabel, Box3d())
{
	add(&resolutions);
	add(&boundingBox);
}

SparseVolumeSceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, -1)
{
	add(&newId);
}

std::string SparseVolumeSceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

bool SparseVolumeSceneCreateCommand::execute(World* world)
{
	/*
	const auto& positions = args.positions.getValue();
	ParticleAttribute attr;
	attr.color = args.color.getValue();
	attr.size = args.pointSize.getValue();
	auto name = args.name.getValue();
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	auto scene = new ParticleSystemScene(world->getNextSceneId(), name, std::move(shape));
	world->addScene(args.layer.getValue(), scene);
	//world->getRenderer()->getBuffer()->screen.add(scene, *world->getGLFactory());
	results.newId.setValue(scene->getId());
	//world->updateViewModel();
	*/
	return true;
}
