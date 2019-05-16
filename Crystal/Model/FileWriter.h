#pragma once

#include <filesystem>
#include "ObjectRepository.h"

namespace Crystal {
	namespace Model {

class FileWriter
{
public:
	bool write(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& objects);

private:
};
	}
}