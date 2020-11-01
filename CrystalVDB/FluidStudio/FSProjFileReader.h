#pragma once

#include "../ThirdParty/nlohmann/include/json.hpp"
#include <string>

namespace PG {
	namespace FS {

class FSProjFileReader
{
public:
	bool read(nlohmann::json json);

	bool read(const std::string& filePath);
};

	}
}