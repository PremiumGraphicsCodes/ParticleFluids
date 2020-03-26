#pragma once

#include "../Graphics/PointLight.h"
#include "IShaderScene.h"
#include "LightShaderBuffer.h"

namespace Crystal {
	namespace Shader {
		class ShaderObject;
	}
	namespace Scene {

class LightShaderScene : public IShader
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