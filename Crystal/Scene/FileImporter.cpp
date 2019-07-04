#include "FileImporter.h"

#include <filesystem>

#include "STLFileImporter.h"
#include "OBJFileImporter.h"
#include "PCDFileImporter.h"

using namespace Crystal::Scene;

bool FileImporter::importFile(const std::experimental::filesystem::path& filePath, Scene& objects, SceneFactory* factory)
{
	const auto format = getFileFormat( filePath.extension() );
	return importFile(filePath, objects, factory, format);
}

bool FileImporter::importFile(const std::experimental::filesystem::path& filePath, Scene& objects, SceneFactory* factory, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
	{
		OBJFileImporter importer(factory);
		const auto isOk = importer.importOBJWithMTL(filePath);
		if (isOk) {
			objects.addScene(importer.getScene());
		}
		return isOk;
	}
	case FileFormat::MTL:
	{
		OBJFileImporter importer(factory);
		return importer.importMTL(filePath);
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
		PCDFileImporter importer;
		return importer.importPCD(filePath, objects);
	}
	default:
		assert(false);
	}
	return false;
}