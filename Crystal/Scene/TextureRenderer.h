#pragma once

#include "IRenderer.h"

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"

namespace Crystal {
	namespace Scene {

class TextureRenderer
{
public:
	TextureRenderer();

	bool build(IRenderer* parent);

	void setTextures(const std::vector<Shader::TextureObject>& textures, Shader::ShaderObject* shader);

	std::string getBuiltInFragmentShaderSource() const;

private:
	//GLBuffer glBuffer;
};

	}
}