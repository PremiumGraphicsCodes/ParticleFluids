#pragma once

#include "STLFile.h"
#include <filesystem>

namespace Crystal {
	namespace IO {

class STLASCIIFileWriter
{
public:
	bool write(const std::filesystem::path& filePath, const STLFile& stl);

	bool write(std::ostream& stream, const STLFile& stl);

private:
};
	}
}