#include "LightRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

LightRepository::LightRepository() :
	nextId(1)
{
	Graphics::PointLight* light = new Graphics::PointLight();
	light->setPosition(glm::vec3(100, 100, 100));
	light->setAmbient(glm::vec4(1, 1, 1, 1));
	light->setDiffuse(glm::vec4(1, 1, 1, 1));
	light->setSpecular(glm::vec4(1, 1, 1, 1));
	LightObject object(nextId++, "Light", light);
	lights.push_back(object);
}

LightRepository::~LightRepository()
{
	clear();
}

void LightRepository::clear()
{
	for (auto l : lights) {
		delete l.getLight();
	}
	lights.clear();
}

void LightRepository::add(PointLight* l, const std::string& name)
{
	LightObject object(nextId++, name, l);
	lights.push_back(object);
}
