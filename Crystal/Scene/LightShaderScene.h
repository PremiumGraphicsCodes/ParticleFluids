#pragma once

#include "../Graphics/PointLight.h"
#include "IShaderScene.h"

namespace Crystal {
	namespace Shader {
		class ShaderObject;
	}
	namespace Scene {

class LightShaderScene : public IShaderScene
{
public:
	LightShaderScene();

	void setShader(Shader::ShaderObject* shader);

	bool build() override;

	void release() override {}

	void add(const Graphics::PointLight& l);

	void send();

	void render() override {}

	std::string getBuiltInFragmentShaderSource() const;

private:
	Shader::ShaderObject* shader;
	std::vector<Graphics::PointLight> lights;
};

	}
}