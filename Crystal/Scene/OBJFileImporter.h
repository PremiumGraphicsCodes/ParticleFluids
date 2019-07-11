#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Scene {
		class IScene;
		class SceneFactory;

class OBJFileImporter
{
public:
	explicit OBJFileImporter(SceneFactory* sceneFactory);

	bool importOBJ(const std::experimental::filesystem::path& filePath, IScene* scene);

	bool importMTL(const std::experimental::filesystem::path& filePath, IScene* scene);

	bool importOBJWithMTL(const std::experimental::filesystem::path& filePath, IScene* parent);

private:
	SceneFactory* sceneFactory;
};
	}
}