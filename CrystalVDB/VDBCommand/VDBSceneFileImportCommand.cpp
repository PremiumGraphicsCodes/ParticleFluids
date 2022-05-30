#include "VDBSceneFileImportCommand.h"


#include "../CrystalVDB/VDBPointsScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

#include "CrystalVDB/CrystalVDB/VDBFileImporter.h"

#include <iostream>

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel FileFormatLabel = "FileFormat";
	PublicLabel FileFormat_PLY_Label = "PLY";
	PublicLabel FileFormat_PCD_Label = "PCD";
	PublicLabel FileFormat_OBJ_Label = "OBJ";
	PublicLabel FileFormat_STL_Label = "STL";
	PublicLabel NewSceneIdLabel = "NewSceneId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneFileImportCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	fileFormat(::FileFormatLabel, "")
{
	add(&filePath);
	add(&fileFormat);
}

VDBSceneFileImportCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneFileImportCommand::VDBSceneFileImportCommand() :
	ICommand(&args, &results)
{}

VDBSceneFileImportCommand::VDBSceneFileImportCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneFileImportCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFileImportCommand::execute(World* world)
{
	const auto format = args.fileFormat.getValue();
	const auto filePath = args.filePath.getValue();
	VDBScene* scene = new VDBScene(world->getNextSceneId(), "Imported");
	VDBFileImporter importer;
	if (format == FileFormat_PLY_Label) {
		auto points = importer.readPLY(filePath);
		if (points != nullptr) {
			scene->addScene(points);
		}
	}
	else if (format == FileFormat_PCD_Label) {
		auto points = importer.readPCD(filePath);
		if (points != nullptr) {
			scene->addScene(points);
		}
	}
	else if (format == FileFormat_OBJ_Label) {
		auto mesh = importer.readOBJ(filePath);
		if (mesh != nullptr) {
			scene->addScene(mesh);
		}
	}
	else if (format == FileFormat_STL_Label) {
		auto mesh = importer.readSTL(filePath);
		if (mesh != nullptr) {
			scene->add(mesh);
		}
	}
	else {
		assert(false);
		return false;
	}
	results.newSceneId.setValue(scene->getId());
	return true;
}

