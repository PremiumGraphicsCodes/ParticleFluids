#pragma once

#include "IShaderScene.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Scene {
		class IMaterialScene;

class LightShaderScene
{
public:
	void add(const Graphics::PointLight& light) { this->lights.push_back(light); }

	std::vector<Graphics::PointLight> getLights() const { return lights; }

	void update(const int index);

	void addParent(IMaterialScene* parent) { this->parentScenes.push_back(parent); }

private:
	std::vector<Graphics::PointLight> lights;
	std::list<IMaterialScene*> parentScenes;
};

	}
}
