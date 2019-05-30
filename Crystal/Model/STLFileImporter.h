#pragma once

#include <filesystem>

namespace Crystal {
	namespace Model {
		class ObjectRepository;

class STLFileImporter
{
public:
	bool importSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool importSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

private:
	
};
	}
}