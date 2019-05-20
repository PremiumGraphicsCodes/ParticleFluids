#pragma once

#include "MTLFile.h"
#include <filesystem>

namespace Crystal {
	namespace IO {

class MTLFileWriter
{
public:
	bool write(const std::experimental::filesystem::path& filePath, const MTLFile& mtl);

	bool write(std::ostream& stream, const MTLFile& mtl);

private:
};

	}
}
