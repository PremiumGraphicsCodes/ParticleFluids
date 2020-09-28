#pragma once

#include "../ThirdParty/nlohmann/include/json.hpp"
#include "FSScene.h"
#include <string>

namespace PG {
	namespace FS {

class FSProjFileWriter
{
public:
	nlohmann::json write(const FSScene& scene);

	bool write(const std::string& filePath);
};

	}
}