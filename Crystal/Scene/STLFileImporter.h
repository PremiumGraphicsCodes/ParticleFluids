#pragma once

#include <filesystem>

namespace Crystal {
	namespace Model {
		class Scene;

class STLFileImporter
{
public:
	bool importSTLAscii(const std::experimental::filesystem::path& filePath, Scene& objects);

	bool importSTLBinary(const std::experimental::filesystem::path& filePath, Scene& objects);	
};
	}
}