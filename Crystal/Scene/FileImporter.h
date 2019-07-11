#pragma once

#include <filesystem>
#include "Scene.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Scene {

class FileImporter
{
public:
	bool importFile(const std::experimental::filesystem::path& filePath, Scene* parent, SceneFactory* factory);

	bool importFile(const std::experimental::filesystem::path& filePath, Scene* parent, SceneFactory* factory, const FileFormat format);
};

	}
}