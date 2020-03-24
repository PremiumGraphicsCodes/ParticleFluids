#pragma once

#include "../Graphics/PointLight.h"
#include "IShaderScene.h"

namespace Crystal {
	namespace Shader {
		class ShaderObject;
	}
	namespace Scene {

class LightShaderBuffer : public IShaderScene
{
public:
	bool build() override;

	void add(const Graphics::PointLight& l);

	void release() override {}

	void send();

	void render() override {}

	std::vector<Graphics::PointLight> getLights() const { return lights; }

private:
	std::vector<Graphics::PointLight> lights;
};

class LightShaderScene : public IShaderScene
{
public:
	LightShaderScene();

	void setShader(Shader::ShaderObject* shader);

	void setBuffer(const LightShaderBuffer& buffer) { this->buffer = buffer; }

	bool build() override;

	void release() override {}

	void send();

	void render() override {}

	std::string getBuiltInFragmentShaderSource() const;

private:
	Shader::ShaderObject* shader;
	LightShaderBuffer buffer;
};

	}
}