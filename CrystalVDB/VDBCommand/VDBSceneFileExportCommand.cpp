#include "VDBSceneFileExportCommand.h"

#include "../../Crystal/IO/PLYFileWriter.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

#include "CrystalVDB/CrystalVDB/VDBScene.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel FileFormatLabel = "FileFormat";
	PublicLabel FileFormat_PLY_Label = "PLY";
	PublicLabel FileFormat_PCD_Label = "PCD";
	PublicLabel FileFormat_OBJ_Label = "OBJ";
	PublicLabel FileFormat_STL_Label = "STL";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;
using namespace Crystal::IO;

VDBSceneFileExportCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	fileFormat(::FileFormatLabel, ""),
	vdbSceneId(::VDBSceneIdLabel, -1)
{
	add(&filePath);
	add(&fileFormat);
	add(&vdbSceneId);
}

VDBSceneFileExportCommand::Results::Results()
{
}

VDBSceneFileExportCommand::VDBSceneFileExportCommand() :
	ICommand(&args, &results)
{}

VDBSceneFileExportCommand::VDBSceneFileExportCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneFileExportCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFileExportCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBScene*>(args.vdbSceneId.getValue());
	const auto points = scene->getPoints();

	const auto format = args.fileFormat.getValue();
	if (format == FileFormat_PLY_Label) {
		for (auto p : points) {
			const auto isOk = writePLY(p);
			if (!isOk) {
				return false;
			}
		}
	}
	else {
		assert(false);
		return true;
	}
	return true;
}

bool VDBSceneFileExportCommand::writePLY(VDBParticleSystemScene* vdbPoints)
{
	assert(vdbPoints != nullptr);

	const auto filePath = args.filePath.getValue();

	const auto points = vdbPoints->getPositions();
	Crystal::IO::PLYFile ply;
	for (auto p : points) {
		PLYPoint vertex;
		vertex.values.push_back(p.x);
		vertex.values.push_back(p.y);
		vertex.values.push_back(p.z);
		ply.vertices.push_back(vertex);
	}

	Crystal::IO::PLYFileWriter writer;
	const auto isOk = writer.writeBinary(filePath, ply);
	if (!isOk) {
		return false;
	}
	return true;

}
