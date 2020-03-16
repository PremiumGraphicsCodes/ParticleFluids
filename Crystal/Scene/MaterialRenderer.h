#pragma once

#include "IRenderer.h"

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"

namespace Crystal {
	namespace Scene {


class MaterialRenderer
{
public:

	MaterialRenderer();

	bool build(IRenderer* parent);

	//void setBuffer(const GLBuffer& buffer) { this->glBuffer = buffer; }

	//void render(const Graphics::Camera& camera) override;

private:
	//GLBuffer glBuffer;
};

	}
}