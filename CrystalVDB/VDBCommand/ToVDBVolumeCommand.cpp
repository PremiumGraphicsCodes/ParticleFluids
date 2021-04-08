#include "ToVDBVolumeCommand.h"

#include "PublicLabels/ToVDBVolumeLabels.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolumeScene.h"

#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::VDB;


ToVDBVolumeCommand::Args::Args() :
	sparseVolumeId(::SparseVolumeIdLabel, -1),
	vdbVolumeId(::VDBVolumeIdLabel, -1)
{
	add(&sparseVolumeId);
	add(&vdbVolumeId);
}

ToVDBVolumeCommand::Results::Results()
{
}

ToVDBVolumeCommand::ToVDBVolumeCommand() :
	ICommand(&args, &results)
{}

std::string ToVDBVolumeCommand::getName()
{
	return ::CommandNameLabel;
}

bool ToVDBVolumeCommand::execute(World* world)
{
	auto svScene = world->getScenes()->findSceneById<SparseVolumeScene*>(args.sparseVolumeId.getValue());
	if (svScene == nullptr) {
		return false;
	}
	auto vdbVolScene = world->getScenes()->findSceneById<VDBVolumeScene*>(args.vdbVolumeId.getValue());
	if (vdbVolScene == nullptr) {
		return false;
	}

	VDBVolumeConverter converter;
	converter.toVDB(*svScene, vdbVolScene);

	return true;
}
