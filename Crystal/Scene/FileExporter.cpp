#include "FileExporter.h"

#include <filesystem>

#include "OBJFileExporter.h"
#include "STLFileExporter.h"
#include "PCDFileExporter.h"

using namespace Crystal::Math;
using namespace Crystal::Model;

bool FileExporter::exportFile(const std::experimental::filesystem::path& filePath, Scene& objects, AppearanceObjectRepository& appearances)
{
	const auto format = getFileFormat(filePath);
	return exportFile(filePath, objects, appearances, format);
}

bool FileExporter::exportFile(const std::experimental::filesystem::path& filePath, Scene& objects, AppearanceObjectRepository& appearances, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
	{
		OBJFileExporter exporter;
		return exporter.exportOBJ(filePath, objects);
	}
	case FileFormat::MTL :
	{
		OBJFileExporter exporter;
		return exporter.exportMTL(filePath, appearances);
	}
	case FileFormat::STL_ASCII :
	{
		STLFileExporter exporter;
		return exporter.exportSTLAscii(filePath, objects);
	}
	case FileFormat::STL_BINARY :
	{
		STLFileExporter exporter;
		return exporter.exportSTLBinary(filePath, objects);
	}
	case FileFormat::PCD :
	{
		PCDFileExporter exporter;
		return exporter.exportPCD(filePath, objects);
	}
	default :
		assert(false);
	}
	return false;
}



