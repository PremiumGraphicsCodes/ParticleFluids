#pragma once

#include <filesystem>
#include "ObjectRepository.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Model {

class FileWriter
{
public:
	bool write(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects);

	bool write(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects, const FileFormat format);

private:
	bool writeOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool writeSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool writeSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool writePCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};
	}
}