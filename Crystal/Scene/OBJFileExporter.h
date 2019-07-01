#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class Scene;

class OBJFileExporter
{
public:
	bool exportOBJ(const std::experimental::filesystem::path& filePath, Scene& objects);

	bool exportMTL(const std::experimental::filesystem::path& filePath, Scene& objects);
};

	}
}