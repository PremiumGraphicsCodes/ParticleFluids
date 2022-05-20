#pragma once

#include <filesystem>
#include "LabeledValueTree.h"

namespace Crystal {
	namespace Command {

class XMLFileWriter
{
public:
	bool write(const LabeledValueTree& tree, const std::filesystem::path& path);

private:
};

	}
}