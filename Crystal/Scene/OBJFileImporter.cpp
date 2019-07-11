#include "OBJFileImporter.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../IO/OBJFileReader.h"
#include "../IO/MTLFileReader.h"

#include "Scene.h"
#include "FaceGroupScene.h"
//#include "AppearanceObjectRepository.h"

using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Scene;

OBJFileImporter::OBJFileImporter(SceneFactory* sceneFactory) :
	sceneFactory(sceneFactory)
{
}

bool OBJFileImporter::importOBJ(const std::experimental::filesystem::path& filePath, IScene* scene)
{
	OBJFileReader reader;
	if (reader.read(filePath)) {
		const auto& obj = reader.getOBJ();
		const auto& positions = obj.positions;
		const auto& normals = obj.normals;
		const auto& texCoords = obj.texCoords;

		PolygonMesh* polygonMesh = new PolygonMesh();
		VertexFactory* vertexFactory = polygonMesh->getVertexFactory();
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

		auto meshScene = sceneFactory->createPolygonMeshScene(polygonMesh, "PolygonMesh");
		scene->addScene(meshScene);

		std::vector< std::vector<int> > indices;
		for (const auto& g : obj.groups) {
			auto faceGroup = new FaceGroupScene();
			for (const auto& f : g.faces) {
				std::vector<int> indices;
				for (int i = 0; i < f.positionIndices.size(); i++) {
					auto p = positionTable[f.positionIndices[i] - 1];
					auto n = normalTable[f.normalIndices[i] - 1];
					const auto texCoordIndex = f.texCoordIndices[i] - 1;
					if (texCoordIndex >= 0) {
						auto t = texCoordTable[texCoordIndex];
						auto v = vertexFactory->createVertex(p, n, t);
						indices.push_back(v->getId());
					}
					else {
						auto v = vertexFactory->createVertex(p, n);
						indices.push_back(v->getId());
					}
				}
				//indices.push_back(eachIndices);
				int origin = indices[0];
				int i1 = 1;
				int i2 = 2;
				for (int i = 0; i2 < indices.size(); i++) {
					Face f(origin, indices[i1], indices[i2]);
					faceGroup->addFace(f);
					i1++;
					i2++;
				}
			}
			faceGroup->setMaterialName(g.usemtl);
			meshScene->addScene(faceGroup);
		}

		return true;
	}
	return false;
}

bool OBJFileImporter::importMTL(const std::experimental::filesystem::path& filePath, IScene* scene)
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
			scene->addScene( sceneFactory->createMaterialScene(new Material(mat), m.name) );
			//mat.textureId = m.ambientTexture;
		}
		return true;
	}
	return false;
}

bool OBJFileImporter::importOBJWithMTL(const std::experimental::filesystem::path& filePath, IScene* parent)
{
	// path から .objファイル名を取得する．
	auto filename = filePath.parent_path() / filePath.stem();
	filename.concat(".mtl");

	auto scene = sceneFactory->createScene("OBJ");

	// mtl ファイルを読み込む．
	if (!importMTL(filename, scene)) {
		return false;
	}

	// obj ファイルを読み込む．
	if (!importOBJ(filePath, scene)) {
		return false;
	}

	parent->addScene(scene);

	return true;
}