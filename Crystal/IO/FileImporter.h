#pragma once

#include <filesystem>
#include "../Scene/Scene.h"
#include "FileFormat.h"

namespace Crystal {
	namespace IO {

class FileImporter
{
public:
	bool importFile(const std::experimental::filesystem::path& filePath, Scene::IScene* parent, Scene::SceneFactory* factory);

	bool importFile(const std::experimental::filesystem::path& filePath, Scene::IScene* parent, Scene::SceneFactory* factory, const FileFormat format);
};

	}
}