#include "VDBParticleSystemToMeshCommand.h"

#include "PublicLabels/VDBParticleSystemToMeshLabels.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../VDBConverter/VDBParticleSystem.h"
#include "../VDBConverter/ParticleSystemToVolumeConverter.h"
#include "../VDBConverter/VolumeToMeshConverter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBParticleSystemToMeshCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	meshId(::MeshIdLabel, -1)
{
	add(&particleSystemId);
	add(&meshId);
}

VDBParticleSystemToMeshCommand::Results::Results()
{
}

VDBParticleSystemToMeshCommand::VDBParticleSystemToMeshCommand() :
	ICommand(&args, &results)
{}

std::string VDBParticleSystemToMeshCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBParticleSystemToMeshCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.particleSystemId.getValue());
	if (scene == nullptr) {
		return false;
	}
	VDBParticleSystem ps;
	//ps.fromCrystal(*scene->getShape());
	ParticleSystemToVolumeConverter toVolumeConverter;
	auto volume = toVolumeConverter.toVolume(ps);

	VolumeToMeshConverter toMeshConvereter;
	auto mesh = toMeshConvereter.toMesh(*volume);
	return false;
}
