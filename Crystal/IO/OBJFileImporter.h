#pragma once

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class IScene;
		class SceneFactory;
	}
	namespace IO {

class OBJFileImporter
{
public:
	explicit OBJFileImporter(Scene::SceneFactory* sceneFactory);

	bool importOBJ(const std::filesystem::path& filePath, Scene::IScene* scene);

	bool importMTL(const std::filesystem::path& filePath, Scene::IScene* scene);

	bool importOBJWithMTL(const std::filesystem::path& filePath, Scene::IScene* parent);

private:
	Scene::SceneFactory* sceneFactory;
};
	}
}