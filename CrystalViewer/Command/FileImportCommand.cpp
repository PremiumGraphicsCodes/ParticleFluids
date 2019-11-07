#include "FileImportCommand.h"
#include "Public/FileImportLabels.h"

#include "../../Crystal/IO/FileFormat.h"
#include "STLFileImportCommand.h"
#include "PCDFileImportCommand.h"

#include "Command.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

FileImportCommand::Args::Args() :
	filePath(::FilePathLabel, "")
{
	add(&filePath);
}

FileImportCommand::Results::Results() :
	isOk(::IsOkLabel, false)
{
	add(&isOk);
}

std::string FileImportCommand::getName()
{
	return ::FileImportCommandLabel;
}

void FileImportCommand::execute(World* scene)
{
	if (!importFile(args.filePath.getValue(), scene)) {
		results.isOk.value = false;
	}
	//scene->getObjects()
}

bool FileImportCommand::importFile(const std::filesystem::path& filePath, World* world)
{
	const auto format = getFileFormat(filePath);
	return importFile(filePath, world, format);
}

bool FileImportCommand::importFile(const std::filesystem::path& filePath, World* world, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ:
	{
		Command command("OBJFileImport");
		command.setArg("FilePath", args.filePath.getValue());
		command.execute(world);
		//OBJFileImporter importer(factory);
		//return importer.importOBJWithMTL(filePath, parent);
		return false;
	}
	case FileFormat::MTL:
	{
//		OBJFileImporter importer(factory);
//		return importer.importMTL(filePath, parent);
		return false;
	}
	case FileFormat::STL_ASCII:
	{
		STLFileImportCommand command;
		STLFileImportCommand::Args args;
		args.filePath = this->args.filePath;
		args.isBinary.setValue(true);
		command.setArg("FilePath", this->args.filePath.getValue());
		command.setArg("IsBinary", true);
		command.execute(world);
		this->results.isOk.setValue(std::any_cast<bool>(command.getResult("IsOk")));
		return true;
	}
	case FileFormat::STL_BINARY:
	{
		STLFileImportCommand command;
		STLFileImportCommand::Args args;
		args.filePath = this->args.filePath;
		args.isBinary.setValue(true);
		command.setArg("FilePath", this->args.filePath.getValue());
		command.setArg("IsBinary", true);
		command.execute(world);
		this->results.isOk.setValue( std::any_cast<bool>( command.getResult("IsOk") ) );
		return true;
	}
	case FileFormat::PCD:
	{
		PCDFileImportCommand command;
		command.setArg("FilePath", this->args.filePath.getValue());
		command.execute(world);
		this->results.isOk.setValue(std::any_cast<bool>(command.getResult("IsOk")));
		return true;
	}
	default:
		assert(false);
	}
	return false;
}