#pragma once

#include "IShaderScene.h"
#include "../Graphics/Material.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {
		class IMaterialScene;

class TextureShaderScene
{
public:
	/*
	void add(const Graphics::Material& material) { this->materials.push_back(material); }

	std::vector<Graphics::Material> getMaterials() const { return materials; }

	void update(const int index);

	void addParent(IMaterialScene* parent) { this->parentScenes.push_back(parent); }
	*/

private:
	std::vector<Shader::TextureObject> textures;
	std::list<IMaterialScene*> parentScenes;
};

	}
}