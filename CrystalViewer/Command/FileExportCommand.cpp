#include "FileExportCommand.h"

#include "Command.h"

#include "Public/FileExportLabels.h"
#include "Public/OBJFileExportLabels.h"
#include "Public/STLFileExportLabels.h"
#include "Public/PCDFileExportLabels.h"

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

		Crystal::Command::Command command(::OBJFileExportLabels::CommandNameLabel);
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
		/*
		std::vector<int> ids;
		auto scenes = world->getObjects()->findScenes(SceneType::TriangleMeshScene);
		for (auto s : scenes) {
			ids.push_back(s->getId());
		}
		*/

		Crystal::Command::Command command(::OBJFileExportLabels::CommandNameLabel);
		command.setArg(::STLFileExportLabels::FilePathLabel, args.filePath.getValue());
		command.setArg(::STLFileExportLabels::IsBinaryLabel, false);
		return command.execute(world);
	}
	case FileFormat::STL_BINARY :
	{
		Crystal::Command::Command command(::STLFileExportLabels::CommandNameLabel);
		command.setArg(::STLFileExportLabels::FilePathLabel, args.filePath.getValue());
		command.setArg(::STLFileExportLabels::IsBinaryLabel, true);
		return command.execute(world);
	}
	case FileFormat::PCD :
	{
		Crystal::Command::Command command(::PCDFileExportLabels::CommandNameLabel);
		std::vector<int> ids;
		auto scenes = world->getObjects()->findScenes(SceneType::ParticleSystemScene);
		for (auto s : scenes) {
			ids.push_back(s->getId());
		}
		command.setArg(::PCDFileExportLabels::IdsLabel, ids);
		command.setArg(::PCDFileExportLabels::FilePathLabel, args.filePath.getValue());
		return command.execute(world);
	}
	default :
		assert(false);
		return false;
	}
	return false;
}

