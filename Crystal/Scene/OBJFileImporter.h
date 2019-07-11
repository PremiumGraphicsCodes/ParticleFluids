#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Scene {
		class Scene;
		class SceneFactory;

class OBJFileImporter
{
public:
	explicit OBJFileImporter(SceneFactory* sceneFactory);

	bool importOBJ(const std::experimental::filesystem::path& filePath, Scene* scene);

	bool importMTL(const std::experimental::filesystem::path& filePath, Scene* scene);

	bool importOBJWithMTL(const std::experimental::filesystem::path& filePath, Scene* parent);

private:
	SceneFactory* sceneFactory;
};
	}
}