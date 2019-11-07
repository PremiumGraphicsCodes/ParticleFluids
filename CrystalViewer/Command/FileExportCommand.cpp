#include "FileExportCommand.h"

#include "OBJFileExportCommand.h"
#include "STLFileExportCommand.h"
#include "PCDFileExportCommand.h"

#include "Public/FileExportLabels.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

FileExportCommand::Args::Args() :
	id(::IdLabel, -1),
	filePath(::FilePathLabel, "")
{
	add(&id);
	add(&filePath);
}

FileExportCommand::Results::Results() :
	isOk(::IsOkLabel, false)
{
	add(&isOk);
}

std::string FileExportCommand::getName()
{
	return ::FileExportCommandLabel;
}

void FileExportCommand::execute(World* scene)
{
	const auto filePath(args.filePath.getValue());
	const auto format = Crystal::IO::getFileFormat(filePath);
	exportFile(filePath, format, scene);
}

void FileExportCommand::exportFile(const std::filesystem::path& filePath, const FileFormat format, World* world)
{
	switch (format) {
	case FileFormat::OBJ :
	{
		OBJFileExportCommand command;
		command.setArg("filePath", args.filePath.getValue());
		command.execute(world);
		this->results.isOk.setValue( std::any_cast<bool>( command.getResult("IsOk") ) );
		break;
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
		command.execute(world);
		this->results.isOk.setValue(std::any_cast<bool>(command.getResult("IsOk")));
		break;
	}
	case FileFormat::STL_BINARY :
	{
		STLFileExportCommand command;
		command.setArg("filePath", args.filePath.getValue());
		command.setArg("isBinary", true);

		command.execute(world);
		this->results.isOk.setValue(std::any_cast<bool>(command.getResult("IsOk")));
		break;
	}
	case FileFormat::PCD :
	{
		PCDFileExportCommand command;
		command.setArg("Id", args.id.getValue());
		command.setArg("FilePath", args.filePath.getValue());
		command.execute(world);
		this->results.isOk.setValue(std::any_cast<bool>(command.getResult("IsOk")));
		break;
	}
	default :
		assert(false);
	}
}

