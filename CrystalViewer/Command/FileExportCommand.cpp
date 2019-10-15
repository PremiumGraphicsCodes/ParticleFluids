#include "FileExportCommand.h"

#include "OBJFileExportCommand.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string FileExportCommand::getName()
{
	return "FileExport";
}

void FileExportCommand::execute(World* scene)
{
	//scene->getObjects()
}

bool FileExportCommand::exportFile(const std::filesystem::path& filePath)
{
	const auto format = Crystal::IO::getFileFormat(filePath);
	return exportFile(filePath, format);
}

bool FileExportCommand::exportFile(const std::filesystem::path& filePath, const FileFormat format)
{
	/*
	switch (format) {
	case FileFormat::OBJ :
	{
		OBJFileExportCommand exporter;
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
	*/
	return false;
}

