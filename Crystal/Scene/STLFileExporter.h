#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class Scene;
		class AppearanceObjectRepository;

class STLFileExporter
{
public:
	bool exportSTLAscii(const std::experimental::filesystem::path& filePath, Scene& objects);

	bool exportSTLBinary(const std::experimental::filesystem::path& filePath, Scene& objects);
};

	}
}