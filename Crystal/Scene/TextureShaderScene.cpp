#include "TextureShaderScene.h"

#include "../Shader/TextureObject.h"

#include <sstream>


using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

TextureShaderScene::TextureShaderScene()
{
}

bool TextureShaderScene::build(ShaderObject* shader)
{
	for (int i = 0; i < 8; ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		shader->findUniformLocation(prefix);
	}
	return true;
}

void TextureShaderScene::setTextures(const std::vector<TextureObject>& textures, ShaderObject* shader)
{
	shader->bind();
	for (int i = 0; i < textures.size(); ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		shader->sendUniform(prefix, textures[i]);
	}
	shader->unbind();
}

/*
std::string LightRenderer::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "struct LightInfo {" << std::endl
		<< "	vec3 position;" << std::endl
		<< "	vec3 La;" << std::endl
		<< "	vec3 Ld;" << std::endl
		<< "	vec3 Ls;" << std::endl
		<< "};"
		<< "uniform LightInfo lights[8];";
	return stream.str();
}
*/