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

private:
	bool exportSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool exportSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool exportPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};
	}
}