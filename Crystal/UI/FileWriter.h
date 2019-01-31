#pragma once

#include <filesystem>
#include "ObjectRepository.h"

namespace Crystal {
	namespace UI {

class FileWriter
{
public:
	bool write(const std::experimental::filesystem::path& filePath, const ObjectRepository& objects);

private:
};
	}
}