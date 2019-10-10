#include "FileImportCommand.h"
#include "Public/FileImportLabel.h"

#include "../../Crystal/IO/FileFormat.h"
#include "../../Crystal/IO/OBJFileImporter.h"
#include "../../Crystal/IO/STLFileImporter.h"
#include "../../Crystal/IO/PCDFileImporter.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

FileImportCommand::Args::Args() :
	filePath("FilePath", "")
{
	add(&filePath);
}

FileImportCommand::Results::Results() :
	isOk("IsOk", false)
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
	case FileFormat::PCD:
	{
		PCDFileImporter importer(factory);
		return importer.importPCD(filePath, parent);
	}
	default:
		assert(false);
	}
	return false;
}