#include "MaterialObjectRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::Model;

MaterialObjectRepository::MaterialObjectRepository() :
	nextId(1)
{
}

MaterialObjectRepository::~MaterialObjectRepository()
{
	clear();
}

void MaterialObjectRepository::clear()
{
	for (auto m : materials) {
		delete m->getMaterial();
		delete m;
	}
	materials.clear();
}

int MaterialObjectRepository::add(Material* m, const std::string& name)
{
	MaterialScene* material = new MaterialScene(nextId++, name, m);
	materials.push_back(material);
	return material->getId();
}

MaterialScene* MaterialObjectRepository::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(materials), std::cend(materials), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(materials)) {
		return nullptr;
	}
	return *iter;
}

MaterialScene* MaterialObjectRepository::findByName(const std::string& name) const
{
	auto iter = std::find_if(std::cbegin(materials), std::cend(materials), [=](auto p) {return p->getName() == name; });
	if (iter == std::cend(materials)) {
		return nullptr;
	}
	return *iter;

}
