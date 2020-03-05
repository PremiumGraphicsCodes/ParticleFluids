#include "FileImportCommand.h"
#include "Public/FileImportLabels.h"

#include "../../Crystal/IO/FileFormat.h"

#include "Public/OBJFileImportLabels.h"
#include "Public/PCDFileImportLabels.h"
#include "Public/STLFileImportLabels.h"

#include "Command.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

FileImportCommand::Args::Args() :
	filePath(FileImportLabels::FilePathLabel, std::string(""))
{
	add(&filePath);
}

FileImportCommand::Results::Results() :
	isOk(FileImportLabels::IsOkLabel, false)
{
	add(&isOk);
}

std::string FileImportCommand::getName()
{
	return FileImportLabels::FileImportCommandLabel;
}

bool FileImportCommand::execute(World* scene)
{
	if (!importFile(args.filePath.getValue(), scene)) {
		results.isOk.value = false;
		return false;
	}
	return true;
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
		Command command(::OBJFileImportLabels::CommandNameLabel);
		command.setArg(::OBJFileImportLabels::FilePathLabel, args.filePath.getValue());
		const auto isOk = command.execute(world);
		//OBJFileImporter importer(factory);
		//return importer.importOBJWithMTL(filePath, parent);
		return isOk;
	}
	case FileFormat::MTL:
	{
//		OBJFileImporter importer(factory);
//		return importer.importMTL(filePath, parent);
		return false;
	}
	case FileFormat::STL:
	{
		Command command(STLFileImportLabels::CommandNameLabel);
		command.setArg(STLFileImportLabels::FilePathLabel, this->args.filePath.getValue());
		const auto isOk = command.execute(world);
		return isOk;
	}
	case FileFormat::PCD:
	{
		Command command(::PCDFileImportLabels::CommandNameLabel);
		command.setArg(::PCDFileImportLabels::FilePathLabel, this->args.filePath.getValue());
		const auto isOk = command.execute(world);
		return isOk;
	}
	default:
		assert(false);
	}
	return false;
}