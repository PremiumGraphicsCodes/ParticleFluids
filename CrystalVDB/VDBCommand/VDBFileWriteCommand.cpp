#include "VDBFileWriteCommand.h"

#include "../CrystalVDB/VDBFileWriter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "PublicLabels/VDBFileWriteLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBFileWriteCommand::Args::Args() :
	particleSystemIds(::ParticleSystemIdsLabel, {}),
	filePath(::FilePathLabel, "")
{
	add(&particleSystemIds);
	add(&filePath);
}

VDBFileWriteCommand::Results::Results()
{
}

VDBFileWriteCommand::VDBFileWriteCommand() :
	ICommand(&args, &results)
{}

std::string VDBFileWriteCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBFileWriteCommand::execute(World* world)
{
	VDBFileWriter writer;
	const auto isOk = writer.open(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	const auto& ids = args.particleSystemIds.getValue();
	for (auto id : ids) {
		auto scene = world->getScenes()->findSceneById<IParticleSystemScene*>(id);
		if (scene == nullptr) {
			return false;
		}
		const auto positions = scene->getPositions();
		writer.write(scene->getName(), positions);
	}

	return true;
}