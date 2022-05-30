#include "VDBSceneVolumeToPointsCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneVolumeToPoints";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel RadiusLabel = "Radius";

	PublicLabel NewSceneIdLabel = "NewSceneId";
}

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "../CrystalVDB/VDBParticleSystemConverter.h"
#include "../CrystalVDB/VDBPolygonMeshConverter.h"
#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneVolumeToPointsCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, -1),
	radius(::RadiusLabel, 5.0)
{
	add(&vdbSceneId);
	add(&radius);
}

VDBSceneVolumeToPointsCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneVolumeToPointsCommand::VDBSceneVolumeToPointsCommand() :
	ICommand(&args, &results)
{}

VDBSceneVolumeToPointsCommand::VDBSceneVolumeToPointsCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{
}

std::string VDBSceneVolumeToPointsCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneVolumeToPointsCommand::execute(World* world)
{
	/*
	auto volume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.vdbVolumeId.getValue());
	if (volume == nullptr) {
		return false;
	}
	auto particleSystem = world->getScenes()->findSceneById<VDBParticleSystemScene*>(args.vdbParticleSystemId.getValue());
	if (particleSystem == nullptr) {
		return false;
	}

	VDBVolumeConverter volumeConverter;
	volumeConverter.toParticleSystem(*volume, particleSystem);

	return true;
	*/
	return false;
}
