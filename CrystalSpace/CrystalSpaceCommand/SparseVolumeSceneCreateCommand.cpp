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
	resolution(::ResolutionLabel, {10, 10, 10}),
	boundingBox(::BoundingBoxLabel, Box3d()),
	name (::NameLabel, std::string("")),
	layer(::LayerLabel, -1)
{
	add(&resolution);
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
	const auto res = args.resolution.getValue();
	auto shape = std::make_unique<SparseVolume>(bb, res);
	auto scene = new SparseVolumeScene(world->getNextSceneId(), name, std::move(shape));
	world->addScene(args.layer.getValue(), scene);
	results.newId.setValue(scene->getId());

	return true;
}
