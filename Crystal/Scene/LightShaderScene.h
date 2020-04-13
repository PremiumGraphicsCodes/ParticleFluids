#pragma once

#include "IShaderScene.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Scene {

class LightShaderScene : public IShaderScene
{
public:
	bool build(Shader::GLObjectFactory& glFactory) { return true; }

	void release(Shader::GLObjectFactory& glFactory) { }

	void render() {}

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec3 position;
};

	}
}