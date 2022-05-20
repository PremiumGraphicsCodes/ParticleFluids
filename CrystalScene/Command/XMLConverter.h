#pragma once

#include <any>
#include "tinyxml2.h"
#include "LabeledValueTree.h"

namespace Crystal {
	namespace Command {

class XMLConverter
{
public:
	static tinyxml2::XMLText* toXML(tinyxml2::XMLDocument* doc, const std::any& value);

	static tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, const LabeledValueTree& tree);

	//static nlohmann::json toJSON(const ICommand& command);

	//static void fromJSON(const nlohmann::json& json, std::any& dest);

	//static void fromJSON(const nlohmann::json& json, Arg<int>& dest);

	//static void fromJSON(const nlohmann::json& json, ICommand& command);

};
	}
}