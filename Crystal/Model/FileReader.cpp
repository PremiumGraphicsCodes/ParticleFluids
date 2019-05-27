#include "FileReader.h"

#include <filesystem>

#include "../IO/OBJFileReader.h"
#include "../IO/MTLFileReader.h"
#include "../IO/STLAsciiFileReader.h"
#include "../IO/STLBinaryFileReader.h"
#include "../IO/PCDFileReader.h"

#include "../Graphics/Material.h"

using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Model;

bool FileReader::read(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances)
{
	const auto format = getFileFormat( filePath.extension() );
	return read(filePath, objects, appearances, format);
}

bool FileReader::read(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
		return readOBJ(filePath, objects);
	case FileFormat::MTL:
		return readMTL(filePath, appearances);
	case FileFormat::STL_ASCII :
		return readSTLAscii(filePath, objects);
	case FileFormat::STL_BINARY :
		return readSTLBinary(filePath, objects);
	case FileFormat::PCD :
		return readPCD(filePath, objects);
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

		std::vector< std::vector<int> > indices;
		for (const auto& f : obj.faces) {
			std::vector<int> eachIndices;
			for (int i = 0; i < f.positionIndices.size(); i++) {
				auto p = positionTable[f.positionIndices[i] - 1];
				auto n = normalTable[f.normalIndices[i] - 1];
				const auto texCoordIndex = f.texCoordIndices[i] - 1;
				if (texCoordIndex != -1) {
					auto t = texCoordTable[texCoordIndex];
					auto v = vertexFactory.createVertex(p, n, t);
					eachIndices.push_back(v);
				}
				else {
					auto v = vertexFactory.createVertex(p, n);
					eachIndices.push_back(v);
				}
			}
			indices.push_back(eachIndices);
		}

		PolygonMeshBuilder builder(std::move(vertexFactory));
		for (const auto& is : indices) {
			int origin = is[0];
			int i1 = 1;
			int i2 = 2;
			for (int i = 0; i2 < is.size(); i++) {
				builder.build({ origin, is[i1], is[i2] });
				i1++;
				i2++;
			}
		}
		objects.getPolygonMeshes()->addObject(builder.getPolygonMesh(), 0, "OBJ");

		return true;
	}
	return false;
}

bool FileReader::readMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& appearances)
{
	MTLFileReader reader;
	if (reader.read(filePath)) {
		const auto& mtl = reader.getMTL();
		for (const auto& m : mtl.materials) {
			Material mat;
			mat.ambient = m.ambient;
			mat.diffuse = m.diffuse;
			mat.specular = m.specular;
			mat.shininess = m.specularExponent;
			//mat.textureId = m.ambientTexture;
		}
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
