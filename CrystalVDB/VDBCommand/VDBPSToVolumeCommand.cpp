#include "VDBPSToVolumeCommand.h"

#include "PublicLabels/VDBPSToVolumeLabels.h"

#include "../../Crystal/Scene/IParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

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
