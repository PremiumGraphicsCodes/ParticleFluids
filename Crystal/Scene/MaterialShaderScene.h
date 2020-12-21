#pragma once

#include "IShaderScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Shader {
		class SmoothRenderer;
	}
	namespace Scene {
		class IMaterialScene;

class MaterialShaderScene
{
public:
	void add(const Graphics::Material& material) { this->materials.push_back(material); }

	std::vector<Graphics::Material> getMaterials() const { return materials; }

	void update(const int index);

private:
	std::vector<Graphics::Material> materials;
	std::list<IMaterialScene*> parentScenes;
};

	}
}