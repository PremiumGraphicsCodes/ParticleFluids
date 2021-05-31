#pragma once

#include <string>

namespace Crystal {
	namespace Shader {

class ShaderBuildStatus
{
public:
	bool isOk;
	std::string log;
};

	}
}