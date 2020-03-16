#pragma once

#include "IRenderer.h"

#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Scene {

class LightRenderer
{
public:
	struct GLBuffer
	{
		void add(const Graphics::PointLight& l);

		std::vector<Graphics::PointLight> lights;
	};

	LightRenderer();

	bool build(IRenderer* parent);

	void setBuffer(const GLBuffer& buffer) { this->glBuffer = buffer; }

	void send(Shader::ShaderObject* shader);

	std::string getBuiltInFragmentShaderSource() const;

private:
	GLBuffer glBuffer;
};

	}
}