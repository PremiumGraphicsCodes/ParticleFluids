#include "LightRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

LightRepository::LightRepository()
{
	Graphics::PointLight* light = new Graphics::PointLight();
	light->setPos(glm::vec3(100, 100, 100));
	light->setAmbient(glm::vec4(1, 1, 1, 1));
	light->setDiffuse(glm::vec4(1, 1, 1, 1));
	light->setSpecular(glm::vec4(1, 1, 1, 1));
	lights.push_back(light);
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
