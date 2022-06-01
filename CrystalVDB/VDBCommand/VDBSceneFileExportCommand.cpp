#include "VDBSceneFileExportCommand.h"


#include "../CrystalVDB/VDBPointsScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

#include "CrystalVDB/CrystalVDB/VDBFileExporter.h"

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
	const auto meshes = scene->getMeshes();

	VDBFileExporter exporter(scene);

	const auto filePath = args.filePath.getValue();
	const auto format = args.fileFormat.getValue();
	if (format == FileFormat_PLY_Label) {
		const auto isOk = exporter.writePLY(filePath);
		return isOk;
	}
	else if (format == FileFormat_PCD_Label) {
		const auto isOk = exporter.writePCD(filePath);
		return isOk;
	}
	else if (format == FileFormat_STL_Label) {
		const auto isOk = exporter.writeSTL(filePath);
		return isOk;
	}
	else if (format == FileFormat_OBJ_Label) {
		assert(false);
		return false;
	}
	else {
		assert(false);
		return false;
	}
	return true;
}

