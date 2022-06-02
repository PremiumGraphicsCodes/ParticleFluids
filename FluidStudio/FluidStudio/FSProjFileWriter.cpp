#include "FSProjFileWriter.h"

#include "MainModel.h"

#include "tinyxml2.h"

using namespace PG::FS;

bool FSProjFileWriter::write(MainModel* model, const std::string& filePath)
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

	model->toXML(&doc, root);

	ret = doc.SaveFile(filePath.c_str());
	if (ret != 0) {
		return false;
	}

	return true;
}

bool FSProjFileWriter::read(MainModel* model, const std::string& filePath)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.LoadFile(filePath.c_str());
	if (ret != 0) {
		//fprintf(stderr, "fail to load xml file: %s\n", file_name);
		return false;
	}

	auto root = doc.RootElement();

	model->fromXML(root);

	return true;
}
