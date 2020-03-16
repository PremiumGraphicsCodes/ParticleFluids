#pragma once

#include "IRenderer.h"

#include "TextureRenderer.h"

#include "../Graphics/Material.h"
#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Scene {

class MaterialRenderer
{
public:
	struct GLBuffer
	{
		void add(const Graphics::Material& m);

		std::vector<Graphics::Material> materials;
	};

	MaterialRenderer();

	bool build(IRenderer* parent);

	void setBuffer(const GLBuffer& buffer) { this->glBuffer = buffer; }

	void send(Shader::ShaderObject* shader);

	std::string getBuiltInFragmentShaderSource() const;

private:
	GLBuffer glBuffer;
};

	}
}