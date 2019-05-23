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
		const auto& obj = reader.getOBJ();
		const auto& positions = obj.positions;
		const auto& normals = obj.normals;
		const auto& texCoords = obj.texCoords;

		VertexFactory vertexFactory;
		for (const auto& p : positions) {
			vertexFactory.createPosition(p);
		}
		for (const auto& n : normals) {
			vertexFactory.createNormal(n);
		}
		for (const auto& tc : texCoords) {
			vertexFactory.createTexCoord(tc);
		}

		const auto& positionTable = vertexFactory.getPositions();
		const auto& normalTable = vertexFactory.getNormals();
		const auto& texCoordTable = vertexFactory.getTexCoords();
		for (const auto& f : obj.faces) {
			for (int i = 0; i < f.positionIndices.size(); i++) {
				auto p = positionTable[f.positionIndices[i] - 1];
				auto n = normalTable[f.normalIndices[i] - 1];
				auto t = texCoordTable[f.texCoordIndices[i] - 1];
				auto v = vertexFactory.createVertex(p, n, t);
			}
		}

		/*
		PolygonMeshBuilder builder(std::move(vertexFactory));
		std::array<int, 3 > indices;
		for (const auto& f : obj.faces) {
			for (int i = 0; i < f.positionIndices.size(); i++) {
				auto p = positionTable[ f.positionIndices[i] - 1 ];
				auto n = normalTable[f.normalIndices[i] - 1];
				auto t = texCoordTable[f.texCoordIndices[i] - 1];

				indices[i] = builder.build( p, n, t);
			}
			builder.build(indices);

		}
		objects.getPolygonMeshes()->addObject(builder.getPolygonMesh(), 0, "OBJ");
		*/

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
		builder.add(mesh);
		builder.build();
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
		builder.add(mesh);
		builder.build();
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
