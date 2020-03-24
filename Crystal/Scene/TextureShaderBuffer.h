#pragma once

#include "IShaderScene.h"

#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class TextureShaderBuffer : public IShaderScene
{
public:
	bool build() override { return true; }

	void release() override {}

	void render() override {}

	void add(const Shader::TextureObject& texture) { textures.push_back(texture); }

private:
	std::vector<Shader::TextureObject> textures;
};

	}
}