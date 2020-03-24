#pragma once

#include "SmoothShaderBuffer.h"

#include "../Graphics/Camera.h"

#include "../Shader/TextureObject.h"
#include "../Shader/VertexBufferObject.h"

#include "MaterialShaderBuffer.h"
#include "MaterialShaderScene.h"
#include "LightShaderScene.h"
#include "TextureShaderScene.h"

namespace Crystal {
	namespace Scene {

class SmoothShaderScene
{
public:
	SmoothShaderScene();

	bool build();

	void send(const SmoothShaderBuffer& buffer, const Graphics::Camera& camera);

	void render();

	LightShaderScene* getLightRenderer() { return &lightShader; }

	TextureShaderScene* getTextureRenderer() { return &textureShader; }

	Shader::ShaderObject* getShader() { return &shader; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	MaterialShaderScene materialShader;
	LightShaderScene lightShader;
	TextureShaderScene textureShader;
	Math::Matrix4df matrix;
	int count;
	Shader::ShaderObject shader;
};

	}
}