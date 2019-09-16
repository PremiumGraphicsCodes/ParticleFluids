#pragma once

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class IScene;
		class SceneFactory;

class PCDFileImporter
{
public:
	explicit PCDFileImporter(SceneFactory* factory);

	bool importPCD(const std::experimental::filesystem::path& filePath, IScene* parent);

private:
	SceneFactory* factory;
};

	}
}