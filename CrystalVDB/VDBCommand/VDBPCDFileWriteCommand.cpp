#include "VDBPCDFileWriteCommand.h"

#include "../../Crystal/IO/PCDBinaryFileWriter.h"

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
	/*
	const auto filePath = args.filePath.getValue();
	Crystal::IO::PCDBinaryFileReader reader;
	const auto isOk = reader.read(filePath);
	if (!isOk) {
		return false;
	}
	const auto pcd = reader.getPCD();
	auto scene = new VDBParticleSystemScene(world->getNextSceneId(), "PCDImport");
	for (const auto& p : pcd.data.positions) {
		scene->add(p, 1.0);
	}
	world->getScenes()->addScene(scene);

	results.vdbPsId.setValue(scene->getId());
	*/
	return true;
}
