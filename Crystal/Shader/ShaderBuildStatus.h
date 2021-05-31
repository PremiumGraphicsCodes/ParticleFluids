#pragma once

#include <string>

namespace Crystal {
	namespace Shader {

class ShaderBuildStatus
{
public:
	bool isOk;
	std::string log;

	void add(const ShaderBuildStatus& rhs)
	{
		this->isOk = this->isOk && rhs.isOk;
		this->log += rhs.log;
	}
};

	}
}