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
	bool importOBJ(const std::experimental::filesystem::path& filePath, Scene& objects);

	bool importMTL(const std::experimental::filesystem::path& filePath, Scene& objects);

	bool importOBJWithMTL(const std::experimental::filesystem::path& filePath, Scene& objects);

private:
	void match(const IO::OBJFile& obj, Scene& appearances);
};
	}
}