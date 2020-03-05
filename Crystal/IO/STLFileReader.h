#pragma once

#include <filesystem>

namespace Crystal {
	namespace IO {

class STLFileReader
{
public:
	bool isBinary(std::istream& in);

	//bool isBinaryFile(const std::filesystem::path& path);
};

	}
}