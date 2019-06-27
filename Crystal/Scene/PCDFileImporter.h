#pragma once

#include <filesystem>

namespace Crystal {
	namespace Model {
		class ObjectRepository;

class PCDFileImporter
{
public:
	bool importPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};

	}
}