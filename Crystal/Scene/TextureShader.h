#pragma once

#include <vector>
#include "IShader.h"
#include "TextureScene.h"

namespace Crystal {
	namespace Scene {
//		class TextureScene;

class TextureShader : public IShader
{
public:
	TextureShader();

	void setShader(Shader::ShaderObject* shader) { this->shader = shader; }

	bool build(Shader::GLObjectFactory& factory) override;

	void send();

	void release(Shader::GLObjectFactory& factory) override {}

	void render() {}

private:
	Shader::ShaderObject* shader;
	std::vector<TextureScene> textureScenes;
};

	}
}