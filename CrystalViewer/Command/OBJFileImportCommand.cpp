#include "OBJFileImportCommand.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/IO/OBJFileReader.h"
#include "../../Crystal/IO/MTLFileReader.h"

#include "../../Crystal/Scene/Scene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

OBJFileImportCommand::Args::Args() :
	filePath("FilePath", std::string(""))
{
	add(&filePath);
}

OBJFileImportCommand::Results::Results() :
	isOk("IsOk", false)
{
	add(&isOk);
}

std::string OBJFileImportCommand::getName()
{
	return "OBJFileImport";
}

void OBJFileImportCommand::execute(World* scene)
{
	const auto result = importOBJ(args.filePath.getValue(), scene);
	results.isOk.setValue(result);
}

bool OBJFileImportCommand::importOBJ(const std::filesystem::path& filePath, World* world)
{
	OBJFileReader reader;
	if (reader.read(filePath)) {
		const auto& obj = reader.getOBJ();
		const auto& positions = obj.positions;
		const auto& normals = obj.normals;
		const auto& texCoords = obj.texCoords;

		PolygonMeshBuilder builder;
		for (const auto& p : positions) {
			builder.createPosition(p);
		}
		for (const auto& n : normals) {
			builder.createNormal(n);
		}
		for (const auto& tc : texCoords) {
			builder.createTexCoord(tc);
		}

		auto polygonMesh = builder.build();
		auto meshScene = world->getSceneFactory()->createPolygonMeshScene(polygonMesh, "PolygonMesh");

		std::vector< std::vector<int> > indices;
		for (const auto& g : obj.groups) {
			auto faceGroup = world->getSceneFactory()->createFaceGroupScene(meshScene, g.name);
			for (const auto& f : g.faces) {
				std::vector<int> indices;
				for (int i = 0; i < f.positionIndices.size(); i++) {
					const auto p = f.positionIndices[i] - 1;
					const auto n = f.normalIndices[i] - 1;
					const auto tc = f.texCoordIndices[i] - 1;
					const auto v = builder.createVertex(p, n, tc);
					indices.push_back(v);
				}
				//indices.push_back(eachIndices);
				int origin = indices[0];
				int i1 = 1;
				int i2 = 2;
				for (int i = 0; i2 < indices.size(); i++) {
					builder.createFace(origin, indices[i1], indices[i2]);
					i1++;
					i2++;
				}
//				faceGroup->addFace(f);
			}
			faceGroup->setMaterialName(g.usemtl);
		}
		world->getObjects()->addScene(meshScene);

		return true;
	}
	return false;
}

bool OBJFileImportCommand::importMTL(const std::filesystem::path& filePath, World* world)
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
			world->getObjects()->addScene(world->getSceneFactory()->createMaterialScene(mat, m.name));
			//mat.textureId = m.ambientTexture;
		}
		return true;
	}
	return false;
}

bool OBJFileImportCommand::importOBJWithMTL(const std::filesystem::path& filePath, World* world)
{
	// path から .objファイル名を取得する．
	auto filename = filePath.parent_path() / filePath.stem();
	filename.concat(".mtl");

	auto scene = world->getSceneFactory()->createScene("OBJ");

	// mtl ファイルを読み込む．
	if (!importMTL(filename, world)) {
		return false;
	}

	// obj ファイルを読み込む．
	if (!importOBJ(filePath, world)) {
		return false;
	}

	world->getObjects()->addScene(scene);

	return true;
}