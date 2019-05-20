#pragma once

#include <filesystem>
#include "ObjectRepository.h"
#include "AppearanceObjectRepository.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Model {

class FileWriter
{
public:
	bool write(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, Model::AppearanceObjectRepository& appearances);

	bool write(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, Model::AppearanceObjectRepository& appearances, const FileFormat format);

private:
	bool writeOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool writeMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& objects);

	bool writeSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool writeSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool writePCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};
	}
}