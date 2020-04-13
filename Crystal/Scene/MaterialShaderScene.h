#pragma once

#include "IShaderScene.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Scene {

class MaterialShaderScene : public IShaderScene
{
public:
	bool build(Shader::GLObjectFactory& glFactory) = 0;

	void release(Shader::GLObjectFactory& glFactory) = 0;

	void render() = 0;

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;
};

	}
}