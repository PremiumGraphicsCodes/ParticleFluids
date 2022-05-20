#pragma once

#include <any>
#include "tinyxml2.h"
#include "PropertyTree.h"
#include <memory>

namespace Crystal {
	namespace Command {

class XMLConverter
{
public:
	static tinyxml2::XMLText* toXML(tinyxml2::XMLDocument* doc, const std::any& value);

	static tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, const PropertyTree& tree);

	//static nlohmann::json toJSON(const ICommand& command);

	static void fromXML(const tinyxml2::XMLElement& text, std::any& dest);

	static bool fromXML(const tinyxml2::XMLElement& parent, PropertyTree& tree);

	//static void fromJSON(const nlohmann::json& json, ICommand& command);

};
	}
}