#pragma once

#include <filesystem>
#include "ObjectRepository.h"
#include "AppearanceObjectRepository.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Model {

class FileExporter
{
public:
	bool exportFile(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, Model::AppearanceObjectRepository& appearances);

	bool exportFile(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, Model::AppearanceObjectRepository& appearances, const FileFormat format);
};

	}
}