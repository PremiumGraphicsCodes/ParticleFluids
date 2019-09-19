#include "OBJFileImporter.h"

#include "../Scene/PolygonMeshBuilder.h"
#include "../IO/OBJFileReader.h"
#include "../IO/MTLFileReader.h"

#include "../Scene/Scene.h"
//#include "AppearanceObjectRepository.h"
#include "../Scene/PolygonMeshScene.h"

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
		for (const auto& p : positions) {
			polygonMesh->createPosition(p);
		}
		for (const auto& n : normals) {
			polygonMesh->createNormal(n);
		}
		for (const auto& tc : texCoords) {
			polygonMesh->createTexCoord(tc);
		}

		const auto& positionTable = polygonMesh->getPositions();
		const auto& normalTable = polygonMesh->getNormals();
		const auto& texCoordTable = polygonMesh->getTexCoords();

		auto meshScene = sceneFactory->createPolygonMeshScene(polygonMesh, "PolygonMesh");

		std::vector< std::vector<int> > indices;
		for (const auto& g : obj.groups) {
			for (const auto& f : g.faces) {
				std::vector<int> indices;
				for (int i = 0; i < f.positionIndices.size(); i++) {
					const auto p = f.positionIndices[i] - 1;
					const auto n = f.normalIndices[i] - 1;
					const auto tc = f.texCoordIndices[i] - 1;
					const auto v = polygonMesh->createVertex(p, n, tc);
					indices.push_back(v);
				}
				//indices.push_back(eachIndices);
				int origin = indices[0];
				int i1 = 1;
				int i2 = 2;
				for (int i = 0; i2 < indices.size(); i++) {
					polygonMesh->createFace(origin, indices[i1], indices[i2]);
					i1++;
					i2++;
				}
			}
			auto faceGroup = sceneFactory->createFaceGroupScene(meshScene, g.name);
			faceGroup->setMaterialName(g.usemtl);
		}
		scene->addScene(meshScene);

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
			scene->addScene( sceneFactory->createMaterialScene(mat, m.name) );
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