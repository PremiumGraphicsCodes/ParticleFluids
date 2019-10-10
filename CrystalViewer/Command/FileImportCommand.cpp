#include "FileImportCommand.h"
#include "Public/FileImportLabel.h"

#include "../../Crystal/IO/FileFormat.h"
#include "../../Crystal/IO/OBJFileImporter.h"
#include "../../Crystal/IO/STLFileImporter.h"
#include "PCDFileImportCommand.h"

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
	if (!importFile(args.filePath.getValue(), scene->getObjects(), scene->getObjectFactory())) {
		results.isOk.value = false;
	}
	//scene->getObjects()
}

bool FileImportCommand::importFile(const std::filesystem::path& filePath, IScene* parent, SceneFactory* factory)
{
	const auto format = getFileFormat(filePath.extension());
	return importFile(filePath, parent, factory, format);
}

bool FileImportCommand::importFile(const std::filesystem::path& filePath, IScene* parent, SceneFactory* factory, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ:
	{
		OBJFileImporter importer(factory);
		return importer.importOBJWithMTL(filePath, parent);
	}
	case FileFormat::MTL:
	{
		OBJFileImporter importer(factory);
		return importer.importMTL(filePath, parent);
	}
	case FileFormat::STL_ASCII:
	{
		STLFileImporter importer(factory);
		return importer.importSTLAscii(filePath, parent);
	}
	case FileFormat::STL_BINARY:
	{
		STLFileImporter importer(factory);
		return importer.importSTLBinary(filePath, parent);
	}
	/*
	case FileFormat::PCD:
	{
		PCDFileImportCommand importer(factory);
		return importer.importPCD(filePath, parent);
	}
	*/
	default:
		assert(false);
	}
	return false;
}