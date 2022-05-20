#include "XMLFileReader.h"
#include "tinyxml2.h"

#include "XMLConverter.h"

using namespace Crystal::Command;

bool XMLFileReader::read(const std::filesystem::path& path, const ILabeledValueFactory& factory)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.LoadFile(path.string().c_str());
	if (ret != 0) {
		//fprintf(stderr, "fail to load xml file: %s\n", file_name);
		return false;
	}

	auto root = doc.RootElement();

	this->tree = std::make_unique<PropertyTree>();
	read(root, factory, *this->tree);

	return true;
}

bool XMLFileReader::read(tinyxml2::XMLElement* parent, const ILabeledValueFactory& factory, PropertyTree& tree)
{
	auto c = parent->FirstChildElement();

	while (c != nullptr) {
		const std::string name = c->Value();
		const auto text = c->GetText();
		if (text == nullptr) {
			auto t = factory.create(name);
			read(c, factory, *t);
		}
		else {
			auto a = tree.getValue(name);
			XMLConverter::fromXML(*c, a);
		}
		c = c->NextSiblingElement();
	}

	return true;
}