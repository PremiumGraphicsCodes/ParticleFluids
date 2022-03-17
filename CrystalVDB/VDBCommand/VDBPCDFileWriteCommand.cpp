#include "VDBPCDFileWriteCommand.h"

#include "../../Crystal/IO/PCDFileWriter.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBPCDFileWrite";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel VDBPSIdLabel = "VDBPSId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPCDFileWriteCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	vdbPsId(::VDBPSIdLabel, -1)
{
	add(&filePath);
	add(&vdbPsId);
}

VDBPCDFileWriteCommand::Results::Results()
{
}

VDBPCDFileWriteCommand::VDBPCDFileWriteCommand() :
	ICommand(&args, &results)
{}

VDBPCDFileWriteCommand::VDBPCDFileWriteCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBPCDFileWriteCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBPCDFileWriteCommand::execute(World* world)
{
	const auto filePath = args.filePath.getValue();

	auto scene = world->getScenes()->findSceneById<VDBParticleSystemScene*>(args.vdbPsId.getValue());
	if (scene == nullptr) {
		return false;
	}

	const auto points = scene->getPositions();
	Crystal::IO::PCDFile pcd;
	pcd.header.points = points.size();
	pcd.header.width = points.size();
	pcd.data.positions = points;

	Crystal::IO::PCDFileWriter writer;
	const auto isOk = writer.writeBinary(filePath, pcd);
	if (!isOk) {
		return false;
	}
	return true;
}
