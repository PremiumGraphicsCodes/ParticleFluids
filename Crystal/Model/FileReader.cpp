#include "FileReader.h"

#include <filesystem>

#include "../IO/OBJFileReader.h"
#include "../IO/STLAsciiFileReader.h"
#include "../IO/STLBinaryFileReader.h"
#include "../IO/PCDFileReader.h"

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Model;

bool FileReader::read(const std::experimental::filesystem::path& filePath, ObjectRepository& repository)
{
	const auto format = getFileFormat( filePath.extension() );
	return read(filePath, repository, format);
}

bool FileReader::read(const std::experimental::filesystem::path& filePath, ObjectRepository& repository, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
		return readOBJ(filePath, repository);
	case FileFormat::STL_ASCII :
		return readSTLAscii(filePath, repository);
	case FileFormat::STL_BINARY :
		return readSTLBinary(filePath, repository);
	case FileFormat::PCD :
		return readPCD(filePath, repository);
	default:
		assert(false);
	}
	return false;
}

bool FileReader::readOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	OBJFileReader reader;
	if (reader.read(filePath)) {
		;
		return true;
	}
	return false;
}

bool FileReader::readSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& repository)
{
	STLASCIIFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.build(mesh);
		repository.getPolygonMeshes()->addObject(builder.getPolygonMesh(), 0, "STL");
		return true;
	}
	return false;
}

bool FileReader::readSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	STLBinaryFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.build(mesh);
		objects.getPolygonMeshes()->addObject(builder.getPolygonMesh(), 0, "STL");
		return true;
	}
	return false;
}

bool FileReader::readPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& repository)
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
