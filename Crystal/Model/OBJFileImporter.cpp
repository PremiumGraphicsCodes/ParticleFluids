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

bool OBJFileImporter::importOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances)
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

		FaceFactory* faceFactory = builder.getFaceFactory();


		const auto& positionTable = vertexFactory->getPositions();
		const auto& normalTable = vertexFactory->getNormals();
		const auto& texCoordTable = vertexFactory->getTexCoords();

		std::vector< std::vector<int> > indices;
		for (const auto& g : obj.groups) {
			for (const auto& f : g.faces) {
				std::vector<int> indices;
				for (int i = 0; i < f.positionIndices.size(); i++) {
					auto p = positionTable[f.positionIndices[i] - 1];
					auto n = normalTable[f.normalIndices[i] - 1];
					const auto texCoordIndex = f.texCoordIndices[i] - 1;
					if (texCoordIndex >= 0) {
						auto t = texCoordTable[texCoordIndex];
						auto v = vertexFactory->createVertex(p, n, t);
						indices.push_back(v);
					}
					else {
						auto v = vertexFactory->createVertex(p, n);
						indices.push_back(v);
					}
				}
				//indices.push_back(eachIndices);
				int origin = indices[0];
				int i1 = 1;
				int i2 = 2;
				for (int i = 0; i2 < indices.size(); i++) {
					faceFactory->createFace({ origin, indices[i1], indices[i2] });
					i1++;
					i2++;
				}
			}
			auto material = appearances.getMaterials()->findByName(g.usemtl);
			const auto materialId = (material) ? material->getId() : -1;
			builder.pushCurrentFaceGroup(materialId);
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

bool OBJFileImporter::importOBJWithMTL(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances)
{
	// path から .objファイル名を取得する．
	auto filename = filePath.parent_path() / filePath.stem();
	filename.concat(".mtl");
	// mtl ファイルを読み込む．
	if (!importMTL(filename, appearances)) {
		return false;
	}

	// obj ファイルを読み込む．
	if (!importOBJ(filePath, objects, appearances)) {
		return false;
	}

	return false;
}

/*
void OBJFileImporter::match(const IO::OBJFile& obj, AppearanceObjectRepository& apperances)
{
	const auto& groups = obj.groups;
	for (const auto& g : groups) {
		auto material = apperances.getMaterials()->findByName(g.usemtl);
		const auto materialId = material->getId();
		for (const auto& f : g.faces) {
			f.
		}
	}
}
*/
