#include "VDBMeshToVolumeCommand.h"

#include "PublicLabels/VDBMeshToVolumeLabels.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/PolygonMeshScene.h"

#include "../CrystalVDB/VDBPolygonMeshConverter.h"
#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBMeshToVolumeCommand::Args::Args() :
	vdbMeshId(::VDBMeshIdLabel, -1),
	vdbVolumeId(::VDBVolumeIdLabel, -1),
	divideLength(::DivideLengthLabel, 1.0f)
{
	add(&vdbMeshId);
	add(&vdbVolumeId);
	add(&divideLength);
}

VDBMeshToVolumeCommand::Results::Results()
{
}

VDBMeshToVolumeCommand::VDBMeshToVolumeCommand() :
	ICommand(&args, &results)
{}

std::string VDBMeshToVolumeCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBMeshToVolumeCommand::execute(World* world)
{
	auto meshScene = world->getScenes()->findSceneById<VDBPolygonMeshScene*>(args.vdbMeshId.getValue());
	if (meshScene == nullptr) {
		return false;
	}
	auto volumeScene = world->getScenes()->findSceneById<VDBVolumeScene*>(args.vdbVolumeId.getValue());
	if (volumeScene == nullptr) {
		return false;
	}

	//meshScene->scale(1.0 / args.divideLength.getValue());

	VDBPolygonMeshConverter converter;
	converter.toVolume(*meshScene, volumeScene, args.divideLength.getValue());

	//volumeScele->

	return true;
}
