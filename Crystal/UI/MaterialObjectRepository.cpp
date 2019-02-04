#include "MaterialObjectRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

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
		delete m.getMaterial();
	}
	materials.clear();
}

void MaterialObjectRepository::add(Material* m, const std::string& name)
{
	MaterialObject material(nextId++, name, m);
	materials.push_back(material);
}
