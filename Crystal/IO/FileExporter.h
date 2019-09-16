#pragma once

#include <filesystem>
#include "../Scene/Scene.h"
#include "FileFormat.h"

namespace Crystal {
	namespace IO {

class FileExporter
{
public:
	bool exportFile(const std::experimental::filesystem::path& filePath, Scene::IScene& objects);

	bool exportFile(const std::experimental::filesystem::path& filePath, Scene::IScene& objects, const FileFormat format);
};

	}
}