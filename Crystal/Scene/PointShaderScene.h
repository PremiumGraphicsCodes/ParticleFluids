#pragma once

#include "IShaderScene.h"
#include "PointBuffer.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"
#include "../Graphics/Camera.h"
#include "../Shader/PointRenderer.h"

namespace Crystal {
	namespace Shader {
		class PointRenderer;
	}
	namespace Scene {

class PointShaderScene : public IShaderScene
{
public:
	explicit PointShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render(const Graphics::Camera& camera) override;

	void send(const PointBuffer& buffer);

	void setShader(Shader::PointRenderer* shader);

	void setBlend(const bool b) { this->doBlend = b; }

private:
	Shader::PointRenderer* shader;
	Shader::PointRenderer::Buffer rBuffer;
	bool doBlend;
};

	}
}