#include "VDBSTLFileReadCommand.h"

#include "Crystal/IO/STLFileReader.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSTLFileRead";
	PublicLabel VDBMeshIdLabel = "VDBMeshId";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSTLFileReadCommand::Args::Args() :
	vdbMeshId(::VDBMeshIdLabel, {}),
	filePath(::FilePathLabel, "")
{
	add(&vdbMeshId);
	add(&filePath);
}

VDBSTLFileReadCommand::Results::Results()
{
}

VDBSTLFileReadCommand::VDBSTLFileReadCommand() :
	ICommand(&args, &results)
{}

std::string VDBSTLFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSTLFileReadCommand::execute(World* world)
{
	auto mesh = world->getScenes()->findSceneById<VDBPolygonMeshScene*>(args.vdbMeshId.getValue());
	if (mesh == nullptr) {
		return false;
	}

	Crystal::IO::STLFileReader reader;
	const auto isOk = reader.readBinary(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	const auto stl = reader.getSTL();
	unsigned int index = 0;
	for (const auto& f : stl.faces) {
		mesh->addVertex(f.triangle.getV0());
		mesh->addVertex(f.triangle.getV1());
		mesh->addVertex(f.triangle.getV2());
		mesh->addTriangle({ index, index + 1, index + 2 });
		index += 3;
	}
	return true;
}