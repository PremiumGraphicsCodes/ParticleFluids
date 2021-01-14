#include "VDBVolumeToMeshCommand.h"

#include "PublicLabels/VDBVolumeToMeshLabels.h"

#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "../CrystalVDB/VDBPolygonMeshConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBVolumeToMeshCommand::Args::Args() :
	vdbVolumeId(::VolumeIdLabel, -1),
	vdbMeshId(::VDBMeshIdLabel, -1)
{
	add(&vdbVolumeId);
	add(&vdbMeshId);
}

VDBVolumeToMeshCommand::Results::Results()
{
}

VDBVolumeToMeshCommand::VDBVolumeToMeshCommand() :
	ICommand(&args, &results)
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
	converter.toMesh(*volume, mesh);

	return true;
}
