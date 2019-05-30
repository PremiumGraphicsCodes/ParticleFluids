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
	bool import(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, Model::AppearanceObjectRepository& appearances);

	bool import(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, Model::AppearanceObjectRepository& appearances, const FileFormat format);

private:
	bool readOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool readMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& appearances);

	bool readSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool readSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool readPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};

	}
}