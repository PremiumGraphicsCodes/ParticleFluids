#include "VDBVolumeToPSCommand.h"

#include "PublicLabels/VDBMeshToParticleSystemLabels.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "../CrystalVDB/VDBParticleSystemConverter.h"
#include "../CrystalVDB/VDBPolygonMeshConverter.h"
#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBVolumeToPSCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	vdbMeshId(::VDBMeshIdLabel, -1),
	radius(::RadiusLabel, 5.0)
{
	add(&particleSystemId);
	add(&vdbMeshId);
	add(&radius);
}

VDBVolumeToPSCommand::Results::Results()
{
}

VDBVolumeToPSCommand::VDBVolumeToPSCommand() :
	ICommand(&args, &results)
{}

std::string VDBVolumeToPSCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBVolumeToPSCommand::execute(World* world)
{
	auto volume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.vdbVolumeId.getValue());
	if (volume == nullptr) {
		return false;
	}
	auto particleSystem = world->getScenes()->findSceneById<IParticleSystemScene*>(args.vdbParticleSystemId.getValue());
	if (particleSystem == nullptr) {
		return false;
	}

	VDBVolumeConverter volumeConverter;
	volumeConverter.toParticleSystem(*volume, particleSystem);

	return true;
}
