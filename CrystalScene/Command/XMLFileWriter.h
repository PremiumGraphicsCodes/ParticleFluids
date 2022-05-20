#pragma once

#include <filesystem>
#include "IArgs.h"

namespace Crystal {
	namespace Command {

class XMLFileWriter
{
public:
	void add(IArgs* arg);

	bool write(const std::filesystem::path& path);

private:
	std::vector<IArgs*> args;
};

	}
}