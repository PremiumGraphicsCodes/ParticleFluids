#pragma once

#include <filesystem>
#include "../Model/ObjectRepository.h"

namespace Crystal {
	namespace UI {

class FileWriter
{
public:
	bool write(const std::experimental::filesystem::path& filePath, const Model::ObjectRepository& objects);

private:
};
	}
}