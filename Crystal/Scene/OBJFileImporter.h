#pragma once

#include "../IO/OBJFile.h"
#include "../IO/MTLFile.h"
#include "SceneFactory.h"
#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class PolygonMeshScene;
		class MaterialScene;
		class Scene;

class OBJFileImporter
{
public:
	explicit OBJFileImporter(SceneFactory* sceneFactory);

	bool importOBJ(const std::experimental::filesystem::path& filePath);

	bool importMTL(const std::experimental::filesystem::path& filePath);

	bool importOBJWithMTL(const std::experimental::filesystem::path& filePath);

	Scene* getScene() { return scene; }

private:
	//void match(const IO::OBJFile& obj, Scene& appearances);
	Scene* scene;
	SceneFactory* sceneFactory;
};
	}
}