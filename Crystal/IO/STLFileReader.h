#pragma once

#include <filesystem>

namespace Crystal {
	namespace IO {

class STLFileReader
{
public:
	static bool isBinary(const std::filesystem::path& filePath);

	static bool isBinary(std::istream& in);

	//bool isBinaryFile(const std::filesystem::path& path);
};

	}
}