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

	bool build(IRenderer* parent);

	void setMaterials(const std::vector<Graphics::Material>& materials, Shader::ShaderObject* shader);
	//void setBuffer(const GLBuffer& buffer) { this->glBuffer = buffer; }

	//void render(const Graphics::Camera& camera) override;

	std::string getBuiltInFragmentShaderSource() const;

private:
	//GLBuffer glBuffer;
};

	}
}