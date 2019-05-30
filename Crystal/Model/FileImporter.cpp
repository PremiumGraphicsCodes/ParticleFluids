#include "FileImporter.h"

#include <filesystem>

#include "../IO/PCDFileReader.h"

#include "STLFileImporter.h"
#include "OBJFileImporter.h"

using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
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
		return readPCD(filePath, objects);
	default:
		assert(false);
	}
	return false;
}

bool FileImporter::readPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& repository)
{
	PCDFileReader reader;
	if (reader.read(filePath)) {
		const auto& positions = reader.getPCD().data.positions;
		ParticleAttribute attr;
		attr.color = glm::vec4(0, 0, 0, 0);
		attr.size = 1.0;
		repository.getParticleSystems()->addObject(positions, attr, "PCD");
		return true;
	}
	return false;
}
