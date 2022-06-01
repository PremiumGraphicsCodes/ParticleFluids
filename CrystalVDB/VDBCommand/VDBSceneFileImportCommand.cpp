#include "VDBSceneFileImportCommand.h"

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
	VDBScene* scene = nullptr;// new VDBScene(world->getNextSceneId(), "Imported");
	VDBFileImporter importer;
	if (format == FileFormat_PLY_Label) {
		scene = importer.readPLY(filePath);
	}
	else if (format == FileFormat_PCD_Label) {
		scene = importer.readPCD(filePath);
	}
	else if (format == FileFormat_OBJ_Label) {
		scene = importer.readOBJ(filePath);
	}
	else if (format == FileFormat_STL_Label) {
		scene = importer.readSTL(filePath);
	}
	else {
		assert(false);
		return false;
	}
	scene->setId(world->getNextSceneId());
	scene->setName("Imported");
	world->addScene(scene);
	results.newSceneId.setValue(scene->getId());
	return true;
}

