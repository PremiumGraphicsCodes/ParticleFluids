#pragma once

#include <filesystem>
#include "ObjectRepository.h"
#include "AppearanceObjectRepository.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Model {

class FileImporter
{
public:
	bool importFile(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, Model::AppearanceObjectRepository& appearances);

	bool importFile(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, Model::AppearanceObjectRepository& appearances, const FileFormat format);

private:

	bool readPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};

	}
}