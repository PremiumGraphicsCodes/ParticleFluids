#pragma once

#include <filesystem>
#include "Scene.h"
#include "AppearanceObjectRepository.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Model {

class FileImporter
{
public:
	bool importFile(const std::experimental::filesystem::path& filePath, Model::Scene& objects, Model::AppearanceObjectRepository& appearances);

	bool importFile(const std::experimental::filesystem::path& filePath, Model::Scene& objects, Model::AppearanceObjectRepository& appearances, const FileFormat format);
};

	}
}