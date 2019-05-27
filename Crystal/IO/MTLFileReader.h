#pragma once

#include "MTLFile.h"

#include <cassert>

#include <fstream>
#include <string>
#include <experimental/filesystem>

namespace Crystal {
	namespace IO {

class MTLFileReader
{
public:
	bool read(const std::experimental::filesystem::path& filePath);

	bool read(std::istream& stream);

	MTLFile getMTL() const { return mtl; }

private:
	MTLFile mtl;
};

	}
}