#pragma once

#include <string>
#include "../Shader/ShaderObject.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"
#include "IShaderScene.h"

namespace Crystal {
	namespace Scene {

class TextureShaderScene
{
public:
	TextureShaderScene();

	void setShader(Shader::ShaderObject* shader) { this->shader = shader; }

	bool build();

	void setTextures(const std::vector<Shader::TextureObject>& textures);

	std::string getBuiltInFragmentShaderSource() const;

private:
	Shader::ShaderObject* shader;
	//GLBuffer glBuffer;
};

	}
}