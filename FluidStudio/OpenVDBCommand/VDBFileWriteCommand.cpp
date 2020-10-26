#include "VDBFileWriteCommand.h"

#include "../OpenVDBConverter/OpenVDBFileWriter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "PublicLabels/VDBFileWriteLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::OpenVDB;

VDBFileWriteCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	filePath(::FilePathLabel, "")
{
	add(&particleSystemId);
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
	auto scene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.particleSystemId.getValue());
	if (scene == nullptr) {
		return false;
	}
	const auto positions = scene->getShape()->getPositions();

	OpenVDBFileWriter writer;
	const auto isOk = writer.open(args.filePath.getValue());
	if (!isOk) {
		return false;
	}

	writer.write(scene->getName(), positions);

	return true;
}