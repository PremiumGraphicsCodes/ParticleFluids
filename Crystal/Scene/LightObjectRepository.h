#pragma once

#include "LightScene.h"
#include <vector>

namespace Crystal {
	namespace Model {

class LightObjectRepository
{
public:
	LightObjectRepository();

	~LightObjectRepository();

	void clear();

	void addLightScene(Graphics::PointLight* l, const std::string& name);

	LightScene* findObjectById(const int id) const;

	std::vector<LightScene*> getLights() const { return lights; }

private:
	std::vector<LightScene*> lights;
	int nextId;
};
	}
}