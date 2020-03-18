#pragma once

#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Shader {
		class ShaderObject;
	}
	namespace Scene {

class LightShaderScene
{
public:
	LightShaderScene();

	bool build(Shader::ShaderObject* shader);

	void add(const Graphics::PointLight& l);

	void send(Shader::ShaderObject* shader);

	std::string getBuiltInFragmentShaderSource() const;

private:
	std::vector<Graphics::PointLight> lights;
};

	}
}