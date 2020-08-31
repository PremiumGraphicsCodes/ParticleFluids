#pragma once

#include "IShaderScene.h"
#include "PointBuffer.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"
#include "../Graphics/Camera.h"
#include "../Shader/PointRenderer.h"
#include "CameraShaderScene.h"

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

	void render() override;

	void send(const PointBuffer& buffer);

	void setShader(Shader::PointRenderer* shader);

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

	CameraShaderScene* getCamera() const { return camera; }

private:
	Shader::PointRenderer* shader;
	Shader::PointRenderer::Buffer rBuffer;
	CameraShaderScene* camera;
};

	}
}