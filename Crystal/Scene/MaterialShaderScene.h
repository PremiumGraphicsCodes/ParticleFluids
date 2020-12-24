#pragma once

#include "IShaderScene.h"
#include "../Graphics/Material.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Scene {
		class IMaterialScene;

class MaterialShaderScene
{
public:
	void add(const Graphics::Material& material) { this->materials.push_back(material); }

	std::vector<Graphics::Material> getMaterials() const { return materials; }

	void updateMaterial(const int index);

	void add(const Graphics::PointLight& light) { this->lights.push_back(light); }

	std::vector<Graphics::PointLight> getLights() const { return lights; }

	void updateLight(const int index);

	void addParent(IMaterialScene* parent) { this->parentScenes.push_back(parent); }

private:
	std::vector<Graphics::Material> materials;
	std::vector<Graphics::PointLight> lights;
	std::list<IMaterialScene*> parentScenes;
};

	}
}