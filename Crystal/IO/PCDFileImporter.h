#pragma once

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class IScene;
		class SceneFactory;
	}
	namespace IO {

class PCDFileImporter
{
public:
	explicit PCDFileImporter(Scene::SceneFactory* factory);

	bool importPCD(const std::filesystem::path& filePath, Scene::IScene* parent);

private:
	Scene::SceneFactory* factory;
};

	}
}