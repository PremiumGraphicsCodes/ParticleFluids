#pragma once

#include "tinyxml2.h"

namespace PG{
	namespace FS {

class IModel
{
public:
	virtual tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent) = 0;
};

	}
}