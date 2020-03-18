#pragma once

#include "IRenderer.h"

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"

namespace Crystal {
	namespace Scene {

class TextureShaderScene
{
public:
	TextureShaderScene();

	bool build(Shader::ShaderObject* shader);

	void setTextures(const std::vector<Shader::TextureObject>& textures, Shader::ShaderObject* shader);

	std::string getBuiltInFragmentShaderSource() const;

private:
	//GLBuffer glBuffer;
};

	}
}