#include "FileExportCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

void FileExportCommand::execute(World* scene)
{
	//scene->getObjects()
}

/*
bool FileExporter::exportFile(const std::filesystem::path& filePath, IScene& objects)
{
	const auto format = getFileFormat(filePath);
	return exportFile(filePath, objects, format);
}

bool FileExporter::exportFile(const std::filesystem::path& filePath, IScene& objects, const FileFormat format)
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
		return exporter.exportMTL(filePath, objects);
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
		return false;
	}
	default :
		assert(false);
	}
	return false;
}
	*/


