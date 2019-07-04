#pragma once

#include <filesystem>
#include "Scene.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Model {

class FileImporter
{
public:
	bool importFile(const std::experimental::filesystem::path& filePath, Model::Scene& objects, SceneFactory* factory);

	bool importFile(const std::experimental::filesystem::path& filePath, Model::Scene& objects, SceneFactory* factory, const FileFormat format);
};

	}
}