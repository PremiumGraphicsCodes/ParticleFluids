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
		OBJFileImporter objImporter;
		return objImporter.importOBJ(filePath, objects);
	}
	case FileFormat::MTL:
	{
		OBJFileImporter objImporter;
		return objImporter.importMTL(filePath, appearances);
	}
	case FileFormat::STL_ASCII :
	{
		STLFileImporter stlImporter;
		return stlImporter.importSTLAscii(filePath, objects);
	}
	case FileFormat::STL_BINARY :
	{
		STLFileImporter stlImporter;
		return stlImporter.importSTLBinary(filePath, objects);
	}
	case FileFormat::PCD :
	{
		PCDFileImporter pcdImporter;
		return pcdImporter.importPCD(filePath, objects);
	}
	default:
		assert(false);
	}
	return false;
}