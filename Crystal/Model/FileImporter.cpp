#include "FileImporter.h"

#include <filesystem>

#include "STLFileImporter.h"
#include "OBJFileImporter.h"
#include "PCDFileImporter.h"

using namespace Crystal::Model;

bool FileImporter::importFile(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances)
{
	const auto format = getFileFormat( filePath.extension() );
	return importFile(filePath, objects, appearances, format);
}

bool FileImporter::importFile(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
	{
		OBJFileImporter importer;
		return importer.importOBJ(filePath, objects, appearances);
	}
	case FileFormat::MTL:
	{
		OBJFileImporter importer;
		return importer.importMTL(filePath, appearances);
	}
	case FileFormat::STL_ASCII :
	{
		STLFileImporter importer;
		return importer.importSTLAscii(filePath, objects);
	}
	case FileFormat::STL_BINARY :
	{
		STLFileImporter importer;
		return importer.importSTLBinary(filePath, objects);
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