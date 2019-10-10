#pragma once

#include <filesystem>
#include "STLFile.h"

namespace Crystal {
	namespace IO {

class STLBinaryFileWriter
{
public:
	bool write(const std::filesystem::path& filePath, const STLFile& stl);

	bool write(std::ostream& stream, const STLFile& stl);

private:
};
	}
}