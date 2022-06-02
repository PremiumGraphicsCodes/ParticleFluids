#include "MainModel.h"

using namespace PG::FS;

void MainModel::init()
{
	solverModel.init(this->world);
}

tinyxml2::XMLElement* MainModel::toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent)
{
	solverModel.toXML(doc, parent);
	return nullptr;
}

bool MainModel::fromXML(tinyxml2::XMLElement* parent)
{
	return solverModel.fromXML(parent);
};
