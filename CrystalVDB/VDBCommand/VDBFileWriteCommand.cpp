#include "VDBFileWriteCommand.h"

#include "../CrystalVDB/VDBFileWriter.h"
#include "../CrystalVDB/VDBVolumeScene.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "OpenVDBFileWrite";
	PublicLabel ParticleSystemIdsLabel = "ParticleSystemIds";
	PublicLabel VDBVolumeIdsLabel = "VDBVolumeIds";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBFileWriteCommand::Args::Args() :
	particleSystemIds(::ParticleSystemIdsLabel, {}),
	vdbVolumeIds(::VDBVolumeIdsLabel, {}),
	filePath(::FilePathLabel, "")
{
	add(&particleSystemIds);
	add(&vdbVolumeIds);
	add(&filePath);
}

VDBFileWriteCommand::Results::Results()
{
}

VDBFileWriteCommand::VDBFileWriteCommand() :
	ICommand(&args, &results)
{}

VDBFileWriteCommand::VDBFileWriteCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBFileWriteCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBFileWriteCommand::execute(World* world)
{
	VDBFileWriter writer;
	const std::string str(args.filePath.getValue());
	const auto isOk = writer.open(str);
	if (!isOk) {
		return false;
	}
	const auto psIds = args.particleSystemIds.getValue();
	for (auto id : psIds) {
		auto scene = world->getScenes()->findSceneById<IParticleSystemScene*>(id);
		if (scene == nullptr) {
			return false;
		}
		const auto positions = scene->getPositions();
		writer.writePoints(scene->getName(), positions);
	}
	const auto volumeIds = args.vdbVolumeIds.getValue();
	std::vector<VDBVolumeScene*> volumes;
	for (auto id : volumeIds) {
		auto scene = world->getScenes()->findSceneById<VDBVolumeScene*>(id);
		if (scene == nullptr) {
			continue;
		}
		volumes.push_back(scene);
	}
	if (!volumes.empty()) {
		writer.writeVolumes(volumes);
	}

	return true;
}