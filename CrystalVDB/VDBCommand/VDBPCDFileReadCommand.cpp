#include "VDBPCDFileReadCommand.h"

#include "../../Crystal/IO/PCDFileReader.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBPCDFileRead";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel VDBPSIdLabel = "VDBPSId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPCDFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, "")
{
	add(&filePath);
}

VDBPCDFileReadCommand::Results::Results() :
	vdbPsId(::VDBPSIdLabel, {})
{
	add(&vdbPsId);
}

VDBPCDFileReadCommand::VDBPCDFileReadCommand() :
	ICommand(&args, &results)
{}

VDBPCDFileReadCommand::VDBPCDFileReadCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBPCDFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBPCDFileReadCommand::execute(World* world)
{
	const auto filePath = args.filePath.getValue();
	Crystal::IO::PCDFileReader reader;
	const auto isOk = reader.readBinary(filePath);
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
	return true;
}
