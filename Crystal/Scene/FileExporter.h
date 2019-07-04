#pragma once

#include <filesystem>
#include "Scene.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Scene {

class FileExporter
{
public:
	bool exportFile(const std::experimental::filesystem::path& filePath, Scene& objects);

	bool exportFile(const std::experimental::filesystem::path& filePath, Scene& objects, const FileFormat format);
};

	}
}