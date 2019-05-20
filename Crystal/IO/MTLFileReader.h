#pragma once

#include "MTLFile.h"

#include <cassert>

#include <fstream>
#include <string>

namespace Crystal {
	namespace IO {

class MTLFileReader
{
public:
	bool read(const std::string& filename);

	bool read(std::istream& stream);

	MTLFile getMTL() const { return mtl; }

private:
	MTLFile mtl;
};

	}
}