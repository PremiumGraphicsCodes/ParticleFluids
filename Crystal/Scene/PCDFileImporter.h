#pragma once

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class Scene;

class PCDFileImporter
{
public:
	bool importPCD(const std::experimental::filesystem::path& filePath, Scene& objects);
};

	}
}