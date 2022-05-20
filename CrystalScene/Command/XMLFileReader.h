#pragma once

#include <filesystem>
#include <map>
#include "tinyxml2.h"
#include "PropertyTree.h"
#include "ILabeledValueFactory.h"

namespace Crystal {
	namespace Command {

class XMLFileReader
{
public:
	bool read(const std::filesystem::path& path, const ILabeledValueFactory& factory);

	std::unique_ptr<PropertyTree> getTree() { return std::move(tree); }

private:
	std::unique_ptr<PropertyTree> tree;
	//std::map<std::string, typeid>

	bool read(tinyxml2::XMLElement* parent, const ILabeledValueFactory& factory);

};

	}
}