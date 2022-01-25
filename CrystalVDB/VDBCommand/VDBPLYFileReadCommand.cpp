#include "VDBPLYFileReadCommand.h"

#include "../../Crystal/IO/PLYFileReader.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBPLYFileRead";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel VDBPSIdLabel = "VDBPSId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPLYFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, "")
{
	add(&filePath);
}

VDBPLYFileReadCommand::Results::Results() :
	vdbPsId(::VDBPSIdLabel, {})
{
	add(&vdbPsId);
}

VDBPLYFileReadCommand::VDBPLYFileReadCommand() :
	ICommand(&args, &results)
{}

VDBPLYFileReadCommand::VDBPLYFileReadCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBPLYFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBPLYFileReadCommand::execute(World* world)
{
	const auto filePath = args.filePath.getValue();
	Crystal::IO::PLYFileReader reader;
	const auto isOk = reader.read(filePath);
	if (!isOk) {
		return false;
	}
	const auto positions = reader.getPositions();
	auto scene = new VDBParticleSystemScene(world->getNextSceneId(), "PCDImport");
	for (const auto& p : positions) {
		scene->add(p, 1.0);
	}
	world->getScenes()->addScene(scene);

	results.vdbPsId.setValue(scene->getId());
	return true;
}