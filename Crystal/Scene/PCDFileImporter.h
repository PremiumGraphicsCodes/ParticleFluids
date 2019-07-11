#pragma once

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class Scene;
		class SceneFactory;

class PCDFileImporter
{
public:
	explicit PCDFileImporter(SceneFactory* factory);

	bool importPCD(const std::experimental::filesystem::path& filePath, Scene* parent);

private:
	SceneFactory* factory;
};

	}
}