#pragma once

#include <filesystem>
#include "ObjectRepository.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Model {

class FileReader
{
public:
	bool read(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& repository);

	bool read(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& repository, const FileFormat format);

private:
	bool readOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool readSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool readSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool readPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};

	}
}