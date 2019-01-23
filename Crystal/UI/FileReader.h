#pragma once

#include <filesystem>
#include "ObjectRepository.h"

namespace Crystal {
	namespace UI {

class FileReader
{
public:
	bool read(const std::experimental::filesystem::path& filePath);

	ObjectRepository getObjects() const { return objects; }

private:
	ObjectRepository objects;
};
	}
}