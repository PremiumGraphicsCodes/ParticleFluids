#include "MaterialObjectRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

MateriaObjectRepository::MateriaObjectRepository() :
	nextId(1)
{
}

MateriaObjectRepository::~MateriaObjectRepository()
{
	clear();
}

void MateriaObjectRepository::clear()
{
	for (auto m : materials) {
		delete m.getMaterial();
	}
	materials.clear();
}

void MateriaObjectRepository::add(Material* m, const std::string& name)
{
	MaterialObject material(nextId++, name, m);
	materials.push_back(material);
}
