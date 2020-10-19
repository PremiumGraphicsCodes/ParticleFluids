#include "OpenVDBFileWriteCommand.h"

#include "../OpenVDBConverter/OpenVDBFileWriter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "OpenVDBFileWrite";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::OpenVDB;

OpenVDBFileWriteCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	filePath(::FilePathLabel, "")
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
	return ::CommandNameLabel;
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