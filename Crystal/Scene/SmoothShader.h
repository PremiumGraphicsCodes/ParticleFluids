#pragma once

#include "SmoothShaderBuffer.h"

#include "../Graphics/Camera.h"
#include "../Graphics/PointLight.h"

#include "../Shader/TextureObject.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/ShaderObject.h"

#include "IShader.h"

namespace Crystal {
	namespace Scene {
		class TextureScene;

		/*
struct TextureShaderBuffer
{
	void add(TextureScene* scenes)
	{

	}

};

class TextureShader : public IShader
{
public:
	TextureShader();

	bool build(Shader::GLObjectFactory& factory) override;

	void release() override;

	void send(const TextureScene& texture);

};
*/


class SmoothShader : public IShader
{
public:
	SmoothShader();

	bool build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void send(const SmoothShaderBuffer& buffer);

	void send(const std::vector<Graphics::Material>& materials);

	void send(const std::vector<Graphics::PointLight>& lights);

	void send(const std::vector<TextureScene>& texture);

	void render() override;

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Math::Matrix4df matrix;
	int count;
	Shader::ShaderObject shader;
};

	}
}