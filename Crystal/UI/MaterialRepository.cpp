#include "MaterialRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

MaterialRepository::MaterialRepository() :
	nextId(1)
{
}

MaterialRepository::~MaterialRepository()
{
	clear();
}

void MaterialRepository::clear()
{
	for (auto m : materials) {
		delete m.getMaterial();
	}
	materials.clear();
}

void MaterialRepository::add(Material* m, const std::string& name)
{
	MaterialObject material(nextId++, name, m);
	materials.push_back(material);
}
