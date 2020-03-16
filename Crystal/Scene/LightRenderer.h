#pragma once

#include "IRenderer.h"

#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Scene {

class LightRenderer
{
public:
	LightRenderer();

	bool build(IRenderer* parent);

	void add(const Graphics::PointLight& l);

	void send(Shader::ShaderObject* shader);

	std::string getBuiltInFragmentShaderSource() const;

private:
	std::vector<Graphics::PointLight> lights;
};

	}
}