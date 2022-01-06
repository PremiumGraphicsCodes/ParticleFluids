#include "VDBVolumeToMeshCommand.h"

#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "../CrystalVDB/VDBPolygonMeshConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBVolumeToMesh";
	PublicLabel VolumeIdLabel = "VolumeId";
	PublicLabel VDBMeshIdLabel = "VDBMeshId";
	PublicLabel ThresholdLabel = "Threshold";
	PublicLabel AdaptivityLabel = "Adaptivity";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBVolumeToMeshCommand::Args::Args() :
	vdbVolumeId(::VolumeIdLabel, -1),
	vdbMeshId(::VDBMeshIdLabel, -1),
	threshold(::ThresholdLabel, 0.0),
	adaptivity(::AdaptivityLabel, 0.0)
{
	add(&vdbVolumeId);
	add(&vdbMeshId);
	add(&threshold);
	add(&adaptivity);
}

VDBVolumeToMeshCommand::Results::Results()
{
}

VDBVolumeToMeshCommand::VDBVolumeToMeshCommand() :
	ICommand(&args, &results)
{}

VDBVolumeToMeshCommand::VDBVolumeToMeshCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBVolumeToMeshCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBVolumeToMeshCommand::execute(World* world)
{
	auto volume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.vdbVolumeId.getValue());
	if (volume == nullptr) {
		return false;
	}
	auto mesh = world->getScenes()->findSceneById<VDBPolygonMeshScene*>(args.vdbMeshId.getValue());
	if (mesh == nullptr) {
		return false;
	}

	VDBVolumeConverter converter;
	converter.toMesh(*volume, mesh, args.threshold.getValue(), args.adaptivity.getValue());

	return true;
}
