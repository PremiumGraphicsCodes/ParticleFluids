#pragma once

#include <string>

namespace PG {
	namespace FS {

class FSProjFileReader
{
public:
	bool read(const std::string& filePath);
};

	}
}