#pragma once

#include <filesystem>
#include <map>
#include "LabeledValueTree.h"
#include "ILabeledValueFactory.h"

namespace Crystal {
	namespace Command {

class XMLFileReader
{
public:
	bool read(const std::filesystem::path& path, const ILabeledValueFactory& factory);

	std::unique_ptr<LabeledValueTree> getTree() { return std::move(tree); }

private:
	std::unique_ptr<LabeledValueTree> tree;
	//std::map<std::string, typeid>
};

	}
}