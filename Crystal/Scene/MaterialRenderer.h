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
	MaterialRenderer();

	void add(const Graphics::Material& m);

	bool build(IRenderer* parent);

	void send(Shader::ShaderObject* shader);

	std::string getBuiltInFragmentShaderSource() const;

private:
	std::vector<Graphics::Material> materials;
};

	}
}