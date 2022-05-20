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

	read(root, factory);

	return true;
}

bool XMLFileReader::read(tinyxml2::XMLElement* parent, const ILabeledValueFactory& factory)
{
	auto attr = parent->FirstChild();
	auto txt = attr->Value();
	auto tree = factory.create(txt);
	const auto values = tree->getValues();
	for (const auto v : values) {
		auto e = attr->FirstChildElement(v->name.c_str());
		auto a = tree->getValue(v->name);
		XMLConverter::fromXML(*e, a);
	}

	return true;
}
