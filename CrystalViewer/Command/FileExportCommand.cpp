#include "FileExportCommand.h"

#include "OBJFileExportCommand.h"
#include "STLFileExportCommand.h"
#include "PCDFileExportCommand.h"

#include "Public/FileExportLabels.h"
#include "Public/OBJFileExportLabels.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

FileExportCommand::Args::Args() :
	filePath(FileExportLabels::FilePathLabel, "")
{
	add(&filePath);
}

FileExportCommand::Results::Results()
{
	//add(&isOk);
}

std::string FileExportCommand::getName()
{
	return FileExportLabels::FileExportCommandLabel;
}

bool FileExportCommand::execute(World* world)
{
	const auto filePath(args.filePath.getValue());
	const auto format = Crystal::IO::getFileFormat(filePath);
	return exportFile(filePath, format, world);
}

bool FileExportCommand::exportFile(const std::filesystem::path& filePath, const FileFormat format, World* world)
{
	switch (format) {
	case FileFormat::OBJ :
	{
		std::vector<int> ids;
		auto scenes = world->getObjects()->findScenes(SceneType::PolygonMeshScene);
		for (auto s : scenes) {
			ids.push_back(s->getId());
		}

		OBJFileExportCommand command;
		command.setArg(::OBJFileExportLabels::FilePathLabel, args.filePath.getValue());
		command.setArg(::OBJFileExportLabels::IdsLabel, ids);
		return command.execute(world);
	}
	/*
	case FileFormat::MTL :
	{
		OBJFileExporter exporter;
		return exporter.exportMTL(filePath, objects);
	}
	*/
	case FileFormat::STL_ASCII :
	{
		STLFileExportCommand command;
		command.setArg("filePath", args.filePath.getValue());
		command.setArg("isBinary", false);
		return command.execute(world);
	}
	case FileFormat::STL_BINARY :
	{
		STLFileExportCommand command;
		command.setArg("filePath", args.filePath.getValue());
		command.setArg("isBinary", true);
		return command.execute(world);
	}
	case FileFormat::PCD :
	{
		PCDFileExportCommand command;
		std::vector<int> ids;
		auto scenes = world->getObjects()->findScenes(SceneType::ParticleSystemScene);
		for (auto s : scenes) {
			ids.push_back(s->getId());
		}
		command.setArg(::FileExportLabels::IdsLabel, ids);
		command.setArg(::FileExportLabels::FilePathLabel, args.filePath.getValue());
		return command.execute(world);
	}
	default :
		assert(false);
		return false;
	}
	return false;
}

