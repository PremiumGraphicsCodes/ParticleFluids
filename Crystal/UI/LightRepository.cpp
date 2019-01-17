#include "LightRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

LightRepository::LightRepository()
{
}

LightRepository::~LightRepository()
{
	clear();
}

void LightRepository::clear()
{
	for (auto l : lights) {
		delete l;
	}
	lights.clear();
}

void LightRepository::add(PointLight* l)
{
	lights.push_back(l);
}
