#include "FileImporter.h"

#include <filesystem>

#include "STLFileImporter.h"
#include "OBJFileImporter.h"
#include "PCDFileImporter.h"

using namespace Crystal::Model;

bool FileImporter::importFile(const std::experimental::filesystem::path& filePath, Scene& objects)
{
	const auto format = getFileFormat( filePath.extension() );
	return importFile(filePath, objects, format);
}

bool FileImporter::importFile(const std::experimental::filesystem::path& filePath, Scene& objects, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
	{
		OBJFileImporter importer;
		return importer.importOBJWithMTL(filePath, objects);
	}
	case FileFormat::MTL:
	{
		OBJFileImporter importer;
		return importer.importMTL(filePath, objects);
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