#include "VDBMeshToParticleSystemCommand.h"

#include "PublicLabels/VDBParticleSystemToMeshLabels.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../VDBConverter/VDBParticleSystem.h"
#include "../VDBConverter/VDBParticleSystemConverter.h"
#include "../VDBConverter/VDBPolygonMeshConverter.h"
#include "../VDBConverter/VDBVolumeConverter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBMeshToParticleSystemCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	vdbMeshId(::VDBMeshIdLabel, -1),
	radius(::RadiusLabel, 5.0)
{
	add(&particleSystemId);
	add(&vdbMeshId);
	add(&radius);
}

VDBMeshToParticleSystemCommand::Results::Results()
{
}

VDBMeshToParticleSystemCommand::VDBMeshToParticleSystemCommand() :
	ICommand(&args, &results)
{}

std::string VDBMeshToParticleSystemCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBMeshToParticleSystemCommand::execute(World* world)
{
	auto meshScene = world->getScenes()->findSceneById<VDBPolygonMesh*>(args.vdbMeshId.getValue());
	if (meshScene == nullptr) {
		return false;
	}
	auto psScene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.particleSystemId.getValue());
	if (psScene == nullptr) {
		return false;
	}

	VDBVolumeScene volume;
	VDBPolygonMeshConverter converter;
	converter.toVolume(*meshScene, &volume);

	VDBParticleSystem ps;
	VDBVolumeConverter volumeConverter;
	volumeConverter.toParticleSystem(volume, &ps);

	VDBParticleSystemConverter psConverter;
	psConverter.fromVDB(ps, psScene);

	return true;
}
