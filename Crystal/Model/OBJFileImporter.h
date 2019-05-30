#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class ObjectRepository;
		class AppearanceObjectRepository;

class OBJFileImporter
{
public:
	bool importOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool importMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& appearances);
};
	}
}