#include "FileExporter.h"

#include <filesystem>

#include "OBJFileExporter.h"
#include "STLFileExporter.h"

#include "../IO/OBJFileWriter.h"
#include "../IO/MTLFileWriter.h"
#include "../IO/STLASCIIFileWriter.h"
#include "../IO/STLBinaryFileWriter.h"
#include "../IO/PCDFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Model;

bool FileExporter::exportFile(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances)
{
	const auto format = getFileFormat(filePath);
	return exportFile(filePath, objects, appearances, format);
}

bool FileExporter::exportFile(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances, const FileFormat format)
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
		return exportPCD(filePath, objects);
	default :
		assert(false);
	}
	return false;
}

bool FileExporter::exportPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	const auto& positions = objects.getParticleSystems()->getAllVertices();
	PCDFile pcd;
	pcd.header.points = positions.size();
	pcd.header.width = positions.size();
	pcd.data.positions = std::vector<Math::Vector3dd>(positions.begin(), positions.end());
	PCDFileWriter writer;
	return writer.write(filePath, pcd);
}

