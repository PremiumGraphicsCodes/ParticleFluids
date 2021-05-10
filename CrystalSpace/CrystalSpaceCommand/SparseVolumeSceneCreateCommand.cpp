#include "SparseVolumeSceneCreateCommand.h"

//#include "../../Crystal/Scene/ParticleAttribute.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "PublicLabels/SparseVolumeSceneCreateLabels.h"

#include "../CrystalSpace/SparseVolumeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SparseVolumeSceneCreateCommand::Args::Args() :
	resolutionX(::ResolutionXLabel, 10),
	resolutionY(::ResolutionYLabel, 10),
	resolutionZ(::ResolutionZLabel, 10),
	boundingBox(::BoundingBoxLabel, Box3d()),
	name (::NameLabel, std::string("")),
	layer(::LayerLabel, -1)
{
	add(&resolutionX);
	add(&resolutionY);
	add(&resolutionZ);
	add(&boundingBox);
	add(&name);
	add(&layer);
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
	auto name = args.name.getValue();

	const auto bb = args.boundingBox.getValue();
	const std::array<int,3> res = 
	{ 
		args.resolutionX.getValue(),
		args.resolutionY.getValue(),
		args.resolutionZ.getValue()
	};
	auto shape = std::make_unique<SparseVolumed>(bb, res);
	auto scene = new SparseVolumeScene(world->getNextSceneId(), name, std::move(shape));
	world->addScene(args.layer.getValue(), scene);
	results.newId.setValue(scene->getId());

	return true;
}
