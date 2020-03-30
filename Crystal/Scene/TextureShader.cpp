#include "TextureShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

TextureShader::TextureShader()
{}

bool TextureShader::build(GLObjectFactory& factory)
{
	/*
	for (int i = 0; i < 8; ++i) {
		factory.getTextureFactory()->createTextureObject("SmoothTex01", Imagef(512, 512));
		const auto prefix = "textures[" + std::to_string(i) + "]";
		shader.findUniformLocation(prefix);
	}
	*/
	return false;
}

void TextureShader::send()
{
	/*
	shader->bind();
	for (int i = 0; i < textures.size(); ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		shader->sendUniform(prefix, textures[i]);
	}
	shader->unbind();
	*/
}