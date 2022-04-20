#include "VDBPSToVolumeCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"
#include "CrystalScene/Scene/IParticleSystemScene.h"
#include "CrystalScene/Scene/PolygonMeshScene.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "../CrystalVDB/VDBParticleSystemConverter.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/SmoothVolumeConverter.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBParticleSystemToVolume";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel VolumeIdLabel = "VolumeId";
	PublicLabel TemperatureVolumeIdLabel = "TemperatureVolumeId";
	PublicLabel RadiusLabel = "Radius";
	PublicLabel VoxelSizeLabel = "VoxelSize";
	PublicLabel DoUseSPHLabel = "DoUseSPH";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPSToVolumeCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	vdbVolumeId(::VolumeIdLabel, -1),
	temperatureVolumeId(::TemperatureVolumeIdLabel, -1),
	radius(::RadiusLabel, 5.0),
	voxelSize(::VoxelSizeLabel, 1.0),
	doUseSph(::DoUseSPHLabel, false)
{
	add(&particleSystemId);
	add(&vdbVolumeId);
	add(&radius);
	add(&voxelSize);
	add(&doUseSph);
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
	auto temperatureVolume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.temperatureVolumeId.getValue());
	if (temperatureVolume == nullptr) {
		return false;
	}

	if (!args.doUseSph.getValue()) {
		VDBParticleSystemConverter psConverter;
		psConverter.toVolume(*scene, args.radius.getValue(), args.voxelSize.getValue(), volume);
	}
	else {
		SmoothVolumeConverter converter;
		converter.buildIsotoropic(scene, args.radius.getValue(), args.voxelSize.getValue(), volume, temperatureVolume);
	}
	return true;
}
