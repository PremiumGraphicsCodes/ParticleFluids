#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class Scene;
		class AppearanceObjectRepository;

class OBJFileExporter
{
public:
	bool exportOBJ(const std::experimental::filesystem::path& filePath, Scene& objects);

	bool exportMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& objects);
};

	}
}