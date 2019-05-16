#pragma once

#include <filesystem>
#include "ObjectRepository.h"

namespace Crystal {
	namespace Model {

class FileReader
{
public:
	bool read(const std::experimental::filesystem::path& filePath, Model::ObjectRepository& repository);

	//ObjectRepository getObjects() const { return objects; }

private:
	//ObjectRepository objects;
};

	}
}