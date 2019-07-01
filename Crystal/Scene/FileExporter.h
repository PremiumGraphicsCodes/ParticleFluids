#pragma once

#include <filesystem>
#include "Scene.h"
#include "FileFormat.h"

namespace Crystal {
	namespace Model {

class FileExporter
{
public:
	bool exportFile(const std::experimental::filesystem::path& filePath, Model::Scene& objects);

	bool exportFile(const std::experimental::filesystem::path& filePath, Model::Scene& objects, const FileFormat format);
};

	}
}