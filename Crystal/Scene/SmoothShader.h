#pragma once

#include "SmoothShaderScene.h"

#include "../Graphics/Camera.h"
#include "../Graphics/PointLight.h"

#include "../Shader/TextureObject.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/ShaderObject.h"

#include "TextureShaderScene.h"

#include "IShader.h"

namespace Crystal {
	namespace Scene {
		class TextureScene;
		class MaterialShaderScene;

class SmoothShader : public IShader
{
public:
	SmoothShader();

	bool build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void send(const SmoothShaderScene& buffer);

	void setMaterialScene(const int index, const MaterialShaderScene& material);

	void send(const std::vector<Graphics::PointLight>& lights);

	//void send(const std::vector<Shader::TextureObject>& textures);

	void render() override;

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	std::vector<Shader::TextureObject> textures;

	Math::Matrix4df matrix;
	int count;
	Shader::ShaderObject shader;

};

	}
}