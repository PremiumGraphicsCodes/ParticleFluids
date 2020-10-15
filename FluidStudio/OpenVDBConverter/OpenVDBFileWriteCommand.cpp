#include "OpenVDBFileWriteCommand.h"

#include "OpenVDBFileWriter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::OpenVDB;

OpenVDBFileWriteCommand::Args::Args() :
	particleSystemId("ParticleSystemId", -1),
	filePath("FilePath", "")
{
	add(&particleSystemId);
	add(&filePath);
}

OpenVDBFileWriteCommand::Results::Results()
{
}

OpenVDBFileWriteCommand::OpenVDBFileWriteCommand() :
	ICommand(&args, &results)
{}

std::string OpenVDBFileWriteCommand::getName()
{
	return "OpenVDBFileWrite";
}

bool OpenVDBFileWriteCommand::execute(World* world)
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