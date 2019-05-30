#include "OBJFileImporter.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../IO/OBJFileReader.h"
#include "../IO/MTLFileReader.h"

#include "ObjectRepository.h"
#include "AppearanceObjectRepository.h"

using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Model;

bool OBJFileImporter::importOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	OBJFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;

		const auto& obj = reader.getOBJ();
		const auto& positions = obj.positions;
		const auto& normals = obj.normals;
		const auto& texCoords = obj.texCoords;

		VertexFactory* vertexFactory = builder.getVertexFactory();
		for (const auto& p : positions) {
			vertexFactory->createPosition(p);
		}
		for (const auto& n : normals) {
			vertexFactory->createNormal(n);
		}
		for (const auto& tc : texCoords) {
			vertexFactory->createTexCoord(tc);
		}

		const auto& positionTable = vertexFactory->getPositions();
		const auto& normalTable = vertexFactory->getNormals();
		const auto& texCoordTable = vertexFactory->getTexCoords();

		std::vector< std::vector<int> > indices;
		for (const auto& g : obj.groups) {
			for (const auto& f : g.faces) {
				std::vector<int> eachIndices;
				for (int i = 0; i < f.positionIndices.size(); i++) {
					auto p = positionTable[f.positionIndices[i] - 1];
					auto n = normalTable[f.normalIndices[i] - 1];
					const auto texCoordIndex = f.texCoordIndices[i] - 1;
					if (texCoordIndex >= 0) {
						auto t = texCoordTable[texCoordIndex];
						auto v = vertexFactory->createVertex(p, n, t);
						eachIndices.push_back(v);
					}
					else {
						auto v = vertexFactory->createVertex(p, n);
						eachIndices.push_back(v);
					}
				}
				indices.push_back(eachIndices);
			}
		}

		FaceFactory* faceFactory = builder.getFaceFactory();
		for (const auto& is : indices) {
			int origin = is[0];
			int i1 = 1;
			int i2 = 2;
			for (int i = 0; i2 < is.size(); i++) {
				faceFactory->createFace({ origin, is[i1], is[i2] });
				i1++;
				i2++;
			}
		}
		objects.getPolygonMeshes()->addObject(builder.getPolygonMesh(), 0, "OBJ");

		return true;
	}
	return false;
}

bool OBJFileImporter::importMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& appearances)
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
			appearances.getMaterials()->add(new Material(mat), m.name);
			//mat.textureId = m.ambientTexture;
		}
		return true;
	}
	return false;
}
