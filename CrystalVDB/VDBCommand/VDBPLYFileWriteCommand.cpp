#include "VDBPLYFileWriteCommand.h"

#include "../../Crystal/IO/PLYFileWriter.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBPLYFileWrite";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel VDBPSIdLabel = "VDBPSId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;
using namespace Crystal::IO;

VDBPLYFileWriteCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	vdbPsId(::VDBPSIdLabel, -1)
{
	add(&filePath);
	add(&vdbPsId);
}

VDBPLYFileWriteCommand::Results::Results()
{
}

VDBPLYFileWriteCommand::VDBPLYFileWriteCommand() :
	ICommand(&args, &results)
{}

VDBPLYFileWriteCommand::VDBPLYFileWriteCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBPLYFileWriteCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBPLYFileWriteCommand::execute(World* world)
{
	const auto filePath = args.filePath.getValue();

	auto scene = world->getScenes()->findSceneById<VDBParticleSystemScene*>(args.vdbPsId.getValue());
	if (scene == nullptr) {
		return false;
	}

	const auto points = scene->getPositions();
	Crystal::IO::PLYFile ply;
	for (auto p : points) {
		PLYPoint vertex;
		vertex.values.push_back(p.x);
		vertex.values.push_back(p.y);
		vertex.values.push_back(p.z);
		ply.vertices.push_back(vertex);
	}
	//ply.vertices.push_back()
	//pcd.header.points = points.size();
	//pcd.header.width = points.size();
	//pcd.data.positions = points;

	Crystal::IO::PLYFileWriter writer;
	const auto isOk = writer.writeBinary(filePath, ply);
	if (!isOk) {
		return false;
	}
	return true;
}