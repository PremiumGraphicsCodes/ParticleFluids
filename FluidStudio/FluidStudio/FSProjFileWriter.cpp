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
	/*
	// User
	tinyxml2::XMLElement* user = doc.NewElement("User");
	user->SetAttribute("Name", "fengbingchun");
	root->InsertEndChild(user);

	tinyxml2::XMLElement* blog = doc.NewElement("Blog");
	tinyxml2::XMLText* text1 = doc.NewText("CSDN");
	blog->InsertEndChild(text1);
	user->InsertEndChild(blog);

	tinyxml2::XMLElement* code = doc.NewElement("Code");
	tinyxml2::XMLText* text2 = doc.NewText("GitHub");
	code->InsertEndChild(text2);
	user->InsertEndChild(code);

	// Blog
	tinyxml2::XMLElement* blog2 = doc.NewElement("Blog");
	blog2->SetAttribute("Name", "CSDN");
	root->InsertEndChild(blog2);

	tinyxml2::XMLElement* addr = doc.NewElement("Address");
	tinyxml2::XMLText* text3 = doc.NewText("https://blog.csdn.net/fengbingchun");
	addr->InsertEndChild(text3);
	blog2->InsertEndChild(addr);

	tinyxml2::XMLElement* id = doc.NewElement("ID");
	tinyxml2::XMLText* text4 = doc.NewText("fengbingchun");
	id->InsertEndChild(text4);
	blog2->InsertEndChild(id);

	// Code
	tinyxml2::XMLElement* code2 = doc.NewElement("Code");
	code2->SetAttribute("Name", "GitHub");
	root->InsertEndChild(code2);

	tinyxml2::XMLElement* addr2 = doc.NewElement("Address");
	tinyxml2::XMLText* text5 = doc.NewText("https://github.com//fengbingchun");
	addr2->InsertEndChild(text5);
	code2->InsertEndChild(addr2);

	tinyxml2::XMLElement* repositories = doc.NewElement("Repositories");
	tinyxml2::XMLText* text6 = doc.NewText("27");
	repositories->InsertEndChild(text6);
	code2->InsertEndChild(repositories);
	*/

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
	return true;
}
