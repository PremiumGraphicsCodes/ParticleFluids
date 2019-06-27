#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class Scene;

class PCDFileExporter
{
public:
	bool exportPCD(const std::experimental::filesystem::path& filePath, Scene& objects);
};

	}
}