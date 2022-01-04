#include "VDBPSToVolumeCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBParticleSystemToMesh";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel VolumeIdLabel = "VolumeId";
	PublicLabel RadiusLabel = "Radius";
}

#include "CrystalScene/Scene/IParticleSystemScene.h"
#include "CrystalScene/Scene/PolygonMeshScene.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "../CrystalVDB/VDBParticleSystemConverter.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPSToVolumeCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	vdbVolumeId(::VolumeIdLabel, -1),
	radius(::RadiusLabel, 5.0)
{
	add(&particleSystemId);
	add(&vdbVolumeId);
	add(&radius);
}

VDBPSToVolumeCommand::Results::Results()
{
}

VDBPSToVolumeCommand::VDBPSToVolumeCommand() :
	ICommand(&args, &results)
{}

VDBPSToVolumeCommand::VDBPSToVolumeCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBPSToVolumeCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBPSToVolumeCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBParticleSystemScene*>(args.particleSystemId.getValue());
	if (scene == nullptr) {
		return false;
	}
	auto volume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.vdbVolumeId.getValue());
	if (volume == nullptr) {
		return false;
	}

	VDBParticleSystemConverter psConverter;
	psConverter.toVolume(*scene, args.radius.getValue(), volume);
	
	return true;
}
