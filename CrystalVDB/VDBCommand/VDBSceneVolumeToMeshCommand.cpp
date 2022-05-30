#include "VDBSceneVolumeToMeshCommand.h"

using namespace Crystal::VDB;

#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "../CrystalVDB/VDBPolygonMeshConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneVolumeToMesh";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel ThresholdLabel = "Threshold";
	PublicLabel AdaptivityLabel = "Adaptivity";

	PublicLabel NewSceneIdLabel = "NewSceneId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneVolumeToMeshCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, -1),
	threshold(::ThresholdLabel, 0.0),
	adaptivity(::AdaptivityLabel, 0.0)
{
	add(&vdbSceneId);
	add(&threshold);
	add(&adaptivity);
}

VDBSceneVolumeToMeshCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneVolumeToMeshCommand::VDBSceneVolumeToMeshCommand() :
	ICommand(&args, &results)
{}

VDBSceneVolumeToMeshCommand::VDBSceneVolumeToMeshCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneVolumeToMeshCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneVolumeToMeshCommand::execute(World* world)
{
	/*
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
	*/
	return false;
}