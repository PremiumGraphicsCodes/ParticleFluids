#pragma once

#include <string>
#include <memory.h>
#include <any>

namespace Crystal {
	namespace Command {

class CommandRunner
{
public:
	void create(const std::string& name);

	void setArg(const std::string& name, std::any value);

	void execute();

	std::any getResult(const std::string& name);
};

	}
}