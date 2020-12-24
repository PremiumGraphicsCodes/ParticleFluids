#pragma once

#include "IShaderScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {
		class ITextureScene;

class TextureShaderScene
{
public:
	void add(Shader::TextureObject* texture) { this->textures.push_back(texture); }

	std::vector<Shader::TextureObject*> getTextures() const { return textures; }

	void update(const int index);

	void addParent(ITextureScene* parent) { this->parentScenes.push_back(parent); }

private:
	std::vector<Shader::TextureObject*> textures;
	std::list<ITextureScene*> parentScenes;
};

	}
}