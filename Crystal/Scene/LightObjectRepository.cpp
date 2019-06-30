#include "LightObjectRepository.h"

using namespace Crystal::Graphics;
using namespace Crystal::Model;

LightObjectRepository::LightObjectRepository() :
	nextId(1)
{
	Graphics::PointLight* light = new Graphics::PointLight();
	light->setPosition(glm::vec3(100, 100, 100));
	light->setAmbient(glm::vec4(1, 1, 1, 1));
	light->setDiffuse(glm::vec4(1, 1, 1, 1));
	light->setSpecular(glm::vec4(1, 1, 1, 1));
	addLightScene(light, "Light");
}

LightObjectRepository::~LightObjectRepository()
{
	clear();
}

void LightObjectRepository::clear()
{
	for (auto l : lights) {
		delete l->getLight();
		delete l;
	}
	lights.clear();

	Graphics::PointLight* light = new Graphics::PointLight();
	light->setPosition(glm::vec3(100, 100, 100));
	light->setAmbient(glm::vec4(1, 1, 1, 1));
	light->setDiffuse(glm::vec4(1, 1, 1, 1));
	light->setSpecular(glm::vec4(1, 1, 1, 1));
	addLightScene(light, "Light");
}

void LightObjectRepository::addLightScene(PointLight* l, const std::string& name)
{
	LightScene* object = new LightScene(nextId++, name, l);
	lights.push_back(object);
}

LightScene* LightObjectRepository::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(lights), std::cend(lights), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(lights)) {
		return nullptr;
	}
	return *iter;
}