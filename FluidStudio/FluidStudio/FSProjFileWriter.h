#pragma once

#include <filesystem>

namespace PG {
	namespace FS {

class FSProjFileWriter
{
public:
	bool write(const std::string& filePath);
};

	}
}