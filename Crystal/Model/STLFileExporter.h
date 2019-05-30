#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class ObjectRepository;
		class AppearanceObjectRepository;

class STLFileExporter
{
public:
	bool exportSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);

	bool exportSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};

	}
}