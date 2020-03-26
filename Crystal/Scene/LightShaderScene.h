#pragma once

#include "../Graphics/PointLight.h"
#include "IShader.h"

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

	void setBuffer(const std::vector<Graphics::PointLight>& buffer) { this->lights = buffer; }

	bool build() override;

	void release() override {}

	void send();

	void render() override {}

	std::string getBuiltInFragmentShaderSource() const;

private:
	Shader::ShaderObject* shader;
	std::vector<Graphics::PointLight> lights;
};

	}
}