#include "MaterialRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

MaterialRepository::MaterialRepository()
{
}

MaterialRepository::~MaterialRepository()
{
	clear();
}

void MaterialRepository::clear()
{
	for (auto m : materials) {
		delete m;
	}
	materials.clear();
}

void MaterialRepository::add(Material* m)
{
	materials.push_back(m);
}
