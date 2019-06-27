#pragma once

#include "../IO/OBJFile.h"
#include "../IO/MTLFile.h"
#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class Scene;
		class AppearanceObjectRepository;

class OBJFileImporter
{
public:
	bool importOBJ(const std::experimental::filesystem::path& filePath, Scene& objects, AppearanceObjectRepository& appearances);

	bool importMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& appearances);

	bool importOBJWithMTL(const std::experimental::filesystem::path& filePath, Scene& objects, AppearanceObjectRepository& appearances);

private:
	void match(const IO::OBJFile& obj, AppearanceObjectRepository& appearances);
};
	}
}