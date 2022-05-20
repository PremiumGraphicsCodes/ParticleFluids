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
	auto attr = root->FirstChild();
	auto txt = attr->Value();
	auto tree = factory.create(txt);

	//tree = std::make_unique<LabeledValueTree>();

	//auto c = root->FirstChild();

	//while (c != root->LastChild()) {
	//	c = c->NextSibling();
	//}

	//auto e = root->FirstChildElement();
	//XMLConverter::fromXML(*root, factory);

	//model->fromXML(root);

	return true;
}
