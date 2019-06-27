#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class ObjectRepository;
		class AppearanceObjectRepository;

class OBJFileExporter
{
public:
	bool exportOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool exportMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& objects);
};

	}
}