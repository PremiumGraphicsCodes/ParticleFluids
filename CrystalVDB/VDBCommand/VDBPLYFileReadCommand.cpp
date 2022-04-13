#include "VDBPLYFileReadCommand.h"

#include "../../Crystal/IO/PLYFileReader.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBPLYFileRead";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IsVolumeLabel = "IsVolume";
	PublicLabel VDBPSIdLabel = "VDBPSId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPLYFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	isVolume(::IsVolumeLabel, false),
	vdbSceneId(::VDBPSIdLabel, -1)
{
	add(&filePath);
	add(&isVolume);
	add(&vdbSceneId);
}

VDBPLYFileReadCommand::Results::Results()
{
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
	auto scene = world->getScenes()->findSceneById<VDBParticleSystemScene*>(args.vdbSceneId.getValue());
	if (scene == nullptr) {
		return false;
	}
	scene->resetImpl();

	const auto filePath = args.filePath.getValue();
	Crystal::IO::PLYFileReader reader;
	const auto isOk = reader.read(filePath);
	if (!isOk) {
		return false;
	}
	const auto ply = reader.getPLY();
	for (const auto& v : ply.vertices) {
		const auto x = v.getValueAs<float>(0);
		const auto y = v.getValueAs<float>(1);
		const auto z = v.getValueAs<float>(2);
		scene->add(Vector3dd(x, y, z), 1.0);
	}

	return true;
}