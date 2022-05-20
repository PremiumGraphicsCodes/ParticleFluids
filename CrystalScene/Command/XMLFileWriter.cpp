#include "XMLFileWriter.h"

#include "XMLFileWriter.h"
#include "XMLConverter.h"
#include <fstream>

#include "tinyxml2.h"

using namespace Crystal::Command;

void XMLFileWriter::add(IArgs* command)
{
	args.push_back(command);
}

bool XMLFileWriter::write(const std::filesystem::path& path)
{
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.Parse(declaration);
	if (ret != 0) {
		fprintf(stderr, "fail to parse xml file: %s\n", declaration);
		return false;
	}

	tinyxml2::XMLComment* comment = doc.NewComment("this is a xml test file");
	doc.InsertEndChild(comment);

	tinyxml2::XMLElement* root = doc.NewElement("Root");
	doc.InsertEndChild(root);

	for (auto& a : args) {
		XMLConverter::toXML(&doc, *a);
	}

	//model->toXML(&doc, root);
	ret = doc.SaveFile(path.string().c_str());
	if (ret != 0) {
		return false;
	}

	return true;
}
