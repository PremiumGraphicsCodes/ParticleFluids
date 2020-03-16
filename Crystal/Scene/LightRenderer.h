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

	void setLights(const std::vector<Graphics::PointLight>& lights, Shader::ShaderObject* shader);

	//void setBuffer(const GLBuffer& buffer) { this->glBuffer = buffer; }

	//void render(const Graphics::Camera& camera) override;

	std::string getBuiltInFragmentShaderSource() const;

private:
	//GLBuffer glBuffer;
};

	}
}