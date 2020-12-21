#pragma once

#include "IShaderScene.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Scene {
		class ILightScene;

class LightShaderScene
{
public:
	void add(const Graphics::PointLight& light) { this->lights.push_back(light); }

	std::vector<Graphics::PointLight> getMaterials() const { return lights; }

	void update(const int index);

	void addParent(ILightScene* parent) { this->parentScenes.push_back(parent); }

private:
	std::vector<Graphics::PointLight> lights;
	std::list<ILightScene*> parentScenes;
};

	}
}
