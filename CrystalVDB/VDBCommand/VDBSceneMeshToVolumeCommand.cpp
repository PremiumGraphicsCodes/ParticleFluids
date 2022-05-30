#include "VDBSceneMeshToVolumeCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneMeshToVolume";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel DivideLengthLabel = "DivideLength";
	PublicLabel NewSceneIdLabel = "NewSceneId";
}

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/PolygonMeshScene.h"

#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"

#include "../CrystalVDB/VDBMeshToVolumeConverter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneMeshToVolumeCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, -1),
	divideLength(::DivideLengthLabel, 1.0f)
{
	add(&vdbSceneId);
	add(&divideLength);
}

VDBSceneMeshToVolumeCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneMeshToVolumeCommand::VDBSceneMeshToVolumeCommand() :
	ICommand(&args, &results)
{}

VDBSceneMeshToVolumeCommand::VDBSceneMeshToVolumeCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneMeshToVolumeCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneMeshToVolumeCommand::execute(World* world)
{
	/*
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
	*/
	return false;
}
