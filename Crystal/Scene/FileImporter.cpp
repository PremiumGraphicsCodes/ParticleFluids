#include "FileImporter.h"

#include <filesystem>

#include "STLFileImporter.h"
#include "OBJFileImporter.h"
#include "PCDFileImporter.h"

using namespace Crystal::Scene;

bool FileImporter::importFile(const std::experimental::filesystem::path& filePath, Scene* parent, SceneFactory* factory)
{
	const auto format = getFileFormat( filePath.extension() );
	return importFile(filePath, parent, factory, format);
}

bool FileImporter::importFile(const std::experimental::filesystem::path& filePath, Scene* parent, SceneFactory* factory, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
	{
		OBJFileImporter importer(factory);
		return importer.importOBJWithMTL(filePath, parent);
	}
	case FileFormat::MTL:
	{
		OBJFileImporter importer(factory);
		return importer.importMTL(filePath, parent);
	}
	case FileFormat::STL_ASCII :
	{
		STLFileImporter importer(factory);
		return importer.importSTLAscii(filePath);
	}
	case FileFormat::STL_BINARY :
	{
		STLFileImporter importer(factory);
		return importer.importSTLBinary(filePath);
	}
	case FileFormat::PCD :
	{
		PCDFileImporter importer(factory);
		return importer.importPCD(filePath, parent);
	}
	default:
		assert(false);
	}
	return false;
}